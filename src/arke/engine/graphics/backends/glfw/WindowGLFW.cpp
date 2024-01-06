#include "WindowGLFW.h"

namespace Arke {
    std::vector<std::string> WindowGLFW::vkRequiredExtensions() {
        return {};
    }

    VkSurfaceKHR WindowGLFW::vkCreateSurface(VkInstance vkInstance) {
        return nullptr;
    }

    void *WindowGLFW::glLoadProc() {
        return (void*) glfwGetProcAddress;
    }

    void WindowGLFW::dispose() {
        glfwTerminate();
    }

    void WindowGLFW::initialize() {
        glfwInit();

        // Configure window hints
        if(this->initOpenGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Consts::OPEN_GL_VERSION.major);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Consts::OPEN_GL_VERSION.minor);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        glfwWindowHint(GLFW_RESIZABLE, this->initResizable);

        this->_handle = glfwCreateWindow(this->initSize.width, this->initSize.height, this->initTitle.c_str(), nullptr, nullptr);

        if(this->initOpenGL) {
            glfwMakeContextCurrent(this->_handle);
        }

        glfwSetWindowUserPointer(this->_handle, this);

        // Register callbacks
        glfwSetKeyCallback(this->_handle, glfwOnKey);
        glfwSetCharCallback(this->_handle, glfwOnChar);
        glfwSetCursorPosCallback(this->_handle, glfwOnCursorPos);
        glfwSetCursorEnterCallback(this->_handle, glfwOnCursorEnter);
        glfwSetMouseButtonCallback(this->_handle, glfwOnMouseButton);
        glfwSetScrollCallback(this->_handle, glfwOnScroll);

        glfwSetFramebufferSizeCallback(this->_handle, glfwOnFramebufferSize);
    }

    IntSize WindowGLFW::size() {
        int width, height;
        glfwGetFramebufferSize(this->_handle, &width, &height);
        return { width, height };
    }

    Looper *WindowGLFW::looper(WindowUpdateReceiver *updater) {
        if(this->_looper == nullptr) {
            this->_looper = new WindowGLFWLooper(this, updater);
        }
        return this->_looper;
    }

    GLFWwindow *WindowGLFW::handle() {
        return this->_handle;
    }


    void WindowGLFW::glfwOnKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
        // TODO Process input
    }

    void WindowGLFW::glfwOnChar(GLFWwindow *window, unsigned int codepoint) {
        // TODO Process input
    }

    void WindowGLFW::glfwOnCursorPos(GLFWwindow *window, double x, double y) {
        // TODO Process input
    }

    void WindowGLFW::glfwOnCursorEnter(GLFWwindow *window, int entered) {
        // TODO Process input
    }

    void WindowGLFW::glfwOnMouseButton(GLFWwindow *window, int button, int action, int mods) {
        // TODO Process input
    }

    void WindowGLFW::glfwOnScroll(GLFWwindow *window, double x, double y) {
        // TODO Process input
    }

    void WindowGLFW::glfwOnFramebufferSize(GLFWwindow *window, int width, int height) {
        auto object = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
        object->_looper->resize({ width, height });
    }

    bool WindowGLFW::shouldClose() {
        return glfwWindowShouldClose(this->_handle);
    }

    void WindowGLFWLooper::resize(IntSize size) const {
        this->receiver->resize(size);
    }

    void WindowGLFWLooper::loop() {
        while(!(this->window->shouldClose() && this->receiver->shouldClose())) {
            this->receiver->update();

            glfwSwapBuffers(this->window->handle());
            glfwPollEvents();
        }
    }
}