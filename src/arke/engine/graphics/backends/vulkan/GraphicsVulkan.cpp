#include <iostream>
#include <map>
#include "GraphicsVulkan.h"
#include "arke/util/String.h"

namespace Arke {
    void GraphicsVulkan::initialize() {
        initInstance();
        initDebugMessenger();
        initPhysicalDevice();

        this->_available = true;
    }

    void GraphicsVulkan::dispose() {
        this->destroyDebugMessenger();

        vkDestroyInstance(this->vkInstance, nullptr);
    }

    bool GraphicsVulkan::available() {
        return this->_available;
    }

    void GraphicsVulkan::initInstance() {
        // Check for validation layers
        if(Consts::VULKAN_ENABLE_VALIDATION_LAYER && !GraphicsVulkan::isValidationLayerSupported()) {
            logger->error("Validation layer was enabled but not supported");
            throw std::runtime_error("Validation layer was enabled but not supported");
        }

        VkApplicationInfo applicationInfo{
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,

                .pApplicationName = this->applicationName.c_str(),
                .applicationVersion = this->applicationVersion.vkMakeVersion(),
                .pEngineName = Consts::ENGINE_NAME.c_str(),
                .engineVersion = Consts::ENGINE_VERSION.vkMakeVersion(),
                .apiVersion = Consts::VULKAN_API_VERSION
        };

        auto requiredExtensions = to_c_str(this->window->vkRequiredExtensions());

        VkInstanceCreateInfo instanceCreateInfo{
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,

                .pApplicationInfo = &applicationInfo,

                .enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size()),
                .ppEnabledExtensionNames = requiredExtensions.data()
        };

        if(Consts::VULKAN_ENABLE_VALIDATION_LAYER) {
            instanceCreateInfo.enabledLayerCount = Consts::VULKAN_VALIDATION_LAYERS.size();
            instanceCreateInfo.ppEnabledLayerNames = Consts::VULKAN_VALIDATION_LAYERS.data();

            auto createInfo = debugMessengerCreateInfo();
            instanceCreateInfo.pNext = &createInfo;
        } else {
            instanceCreateInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &this->vkInstance);
        if(result != VK_SUCCESS) {
            this->logger->error("Failed to create vulkan instance");
        }
    }

    void GraphicsVulkan::initDebugMessenger() {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
        if(!Consts::VULKAN_ENABLE_VALIDATION_LAYER) return;
#pragma clang diagnostic pop

        auto createInfo = debugMessengerCreateInfo();

        auto vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(this->vkInstance, "vkCreateDebugUtilsMessengerEXT");
        if(vkCreateDebugUtilsMessengerEXT == nullptr) {
            this->logger->error("Failed to create debug messenger: vkCreateDebugUtilsMessengerEXT is not found");
            return;
        }

        if(vkCreateDebugUtilsMessengerEXT(this->vkInstance, &createInfo, nullptr, &this->vkDebugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create debug messenger");
        }
    }

    void GraphicsVulkan::initPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(this->vkInstance, &deviceCount, nullptr);
        if(deviceCount == 0) {
            error_throw(this->logger, "Failed to find graphics device supports Vulkan");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(this->vkInstance, &deviceCount, devices.data());

        std::multimap<int, VkPhysicalDevice> candidates;
        for(const auto& device : devices) {
            candidates.insert(std::make_pair(ratePhysicalDevice(device), device));
        }

        if(candidates.rbegin()->first != 0) {
            this->vkPhysicalDevice = candidates.rbegin()->second;
        } else {
            error_throw(this->logger, "Failed to find suitable device!");
        }
    }

    void GraphicsVulkan::destroyDebugMessenger() {
        auto vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(this->vkInstance, "vkDestroyDebugUtilsMessengerEXT");
        if(vkDestroyDebugUtilsMessengerEXT == nullptr) {
            this->logger->error("Failed to dispose debug messenger: vkDestroyDebugUtilsMessengerEXT is not found");
            return;
        }

        vkDestroyDebugUtilsMessengerEXT(this->vkInstance, this->vkDebugMessenger, nullptr);
    }



    bool GraphicsVulkan::isRequiredExtensionsSupported() {
        return false;
    }

    bool GraphicsVulkan::isValidationLayerSupported() {
        auto supportedLayers = GraphicsVulkan::instanceLayerProperties();

        for(const auto& layerName : Consts::VULKAN_VALIDATION_LAYERS) {
            bool layerFound = false;

            for(const auto& layerProperties : supportedLayers) {
                if(strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if(!layerFound) {
                return false;
            }
        }

        return true;
    }

    int GraphicsVulkan::ratePhysicalDevice(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);

        int score = 0;

        if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            score += 1000;
        }

        score += static_cast<int>(properties.limits.maxImageDimension2D);

        if(!features.geometryShader) return 0;

        return score;
    }

    VkDebugUtilsMessengerCreateInfoEXT GraphicsVulkan::debugMessengerCreateInfo() {
        return {
                .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                .messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                               | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                               | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                .pfnUserCallback = validationLayerDebugCallback
        };
    }

    std::vector<VkExtensionProperties> GraphicsVulkan::instanceExtensionProperties() {
        uint32_t extensionCount = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        return extensions;
    }

    std::vector<VkLayerProperties> GraphicsVulkan::instanceLayerProperties() {
        uint32_t layerCount = 0;

        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> layers(layerCount);

        vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

        return layers;
    }

    VkBool32 GraphicsVulkan::validationLayerDebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT severity,
            VkDebugUtilsMessageTypeFlagsEXT type,
            const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
            void *userData
    ) {
        std::cerr << "[Vulkan Validation Layer] " << callbackData->pMessage << std::endl;

        return VK_FALSE;
    }
}
