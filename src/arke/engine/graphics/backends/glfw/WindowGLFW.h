#pragma once

#include <arke/engine/graphics/Window.h>
#include <arke/util/Logging.h>
#include <arke/engine/Consts.h>
#include <arke/util/Disposable.h>

#include "GLFW/glfw3.h"

using namespace util;

namespace Arke {
    class WindowGLFWLooper;

    class WindowGLFW: public Window, public Disposable {
    private:
        logger_t logger = create_logger("Window:GLFW");

        GLFWwindow* _handle = nullptr;

        WindowGLFWLooper* _looper = nullptr;
    public:
        bool initOpenGL = false;
        bool initVulkan = false;

        IntSize initSize = { 800, 600 };
        std::string initTitle = "Arke: WindowGLFW";
        bool initResizable = true;

        std::vector<std::string> vkRequiredExtensions() override;
        VkSurfaceKHR vkCreateSurface(VkInstance vkInstance) override;
        void * glLoadProc() override;

        IntSize size() override;

        Looper* looper(WindowUpdateReceiver* updater) override;

        void dispose() override;

        void initialize();

        bool shouldClose();

        GLFWwindow* handle();
    private:
        // GLFW Callbacks
        static void glfwOnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwOnChar(GLFWwindow* window, unsigned int codepoint);
        static void glfwOnCursorPos(GLFWwindow* window, double x, double y);
        static void glfwOnCursorEnter(GLFWwindow* window, int entered);
        static void glfwOnMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void glfwOnScroll(GLFWwindow* window, double x, double y);

        static void glfwOnFramebufferSize(GLFWwindow* window, int width, int height);
    };

    class WindowGLFWLooper: public Looper {
        friend WindowGLFW;

    public:
        WindowGLFW* window;
        WindowUpdateReceiver* receiver;

    private:
        WindowGLFWLooper(WindowGLFW* window, WindowUpdateReceiver* receiver): window(window), receiver(receiver) {};

        void resize(IntSize size) const;
    public:
        void loop() override;
    };
}