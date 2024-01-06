#pragma once

#include <string>
#include "vulkan/vulkan.h"

#include "arke/util/Version.h"
#include "arke/util/Logging.h"
#include "arke/engine/Consts.h"
#include "arke/engine/graphics/Window.h"
#include "arke/engine/graphics/Graphics.h"

using namespace util;

namespace Arke {
    /**
     * Vulkan <--- 이거걍 좆같음
     */
	class GraphicsVulkan: public Graphics {
    private:
        logger_t logger = create_logger("GraphicsVulkan");

        bool _available = false;

    public:
		std::string applicationName;
        Version applicationVersion;

        Window* window;

        VkInstance vkInstance;
        VkDebugUtilsMessengerEXT vkDebugMessenger;
        VkPhysicalDevice vkPhysicalDevice;

        void initialize() override;
        void dispose() override;

        bool available() override;

        void initInstance();
        void initDebugMessenger();
        void initPhysicalDevice();

        void destroyDebugMessenger();

        bool isRequiredExtensionsSupported();

        int ratePhysicalDevice(VkPhysicalDevice device);

        static VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo();

        static bool isValidationLayerSupported();

        static std::vector<VkExtensionProperties> instanceExtensionProperties();
        static std::vector<VkLayerProperties> instanceLayerProperties();

        static VKAPI_ATTR VkBool32 VKAPI_CALL validationLayerDebugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                VkDebugUtilsMessageTypeFlagsEXT type,
                const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
                void* userData
        );
	};
};