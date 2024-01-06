#pragma once

#include "SDL2/SDL.h"

#include "arke/engine/graphics/Looper.h"
#include "arke/engine/graphics/Window.h"
#include "arke/util/Logging.h"
#include "arke/engine/Consts.h"

using namespace util;

namespace Arke {
    class WindowSDL2: public Window {
    private:
        logger_t logger = create_logger("Window:SDL2");

        SDL_Window* _handle = nullptr;
    public:
        bool initOpenGL = false;
        bool initVulkan = false;

        std::string initTitle;
        bool initFullscreen = false;
        bool initShown = true;
        bool initBorderless = false;
        bool initResizable = false;
        bool initMaximized = false;
        bool initMinimized = false;
        // TODO Should add the other SDL options

        bool initVSync = false;

        SDL_GLContext glContext = nullptr;
    public:
        /////////////////////////////
        // Graphics
        /////////////////////////////
        std::vector<std::string> vkRequiredExtensions() override;
        VkSurfaceKHR vkCreateSurface(VkInstance vkInstance) override;

        void * glLoadProc() override;

        /////////////////////////////
        // Objects
        /////////////////////////////

        void initialize();

        IntSize size() override;

        Looper* looper(WindowUpdateReceiver* updater) override;

        SDL_Window* handle();
    };

    class WindowSDL2Looper: public Looper {
    public:
        WindowSDL2* window;
        WindowUpdateReceiver* receiver;

        explicit WindowSDL2Looper(WindowSDL2* window, WindowUpdateReceiver* updater): window(window), receiver(updater) {};

        void loop() override;
    };
}