#include "WindowSDL2.h"

namespace Arke {
    std::vector<std::string> WindowSDL2::vkRequiredExtensions() {
        return {};
    }

    VkSurfaceKHR WindowSDL2::vkCreateSurface(VkInstance vkInstance) {
        return nullptr;
    }

    void *WindowSDL2::glLoadProc() {
        return (void*) SDL_GL_GetProcAddress;
    }

    IntSize WindowSDL2::size() {
        IntSize size{};
        SDL_GetWindowSize(this->_handle, &size.width, &size.height);
        return size;
    }

    void WindowSDL2::initialize() {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            error_throw(this->logger, "Failed to initialize SDL");
        }
        atexit(SDL_Quit);

        if(this->initOpenGL) {
            SDL_GL_LoadLibrary(nullptr);

            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, true);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, Consts::OPEN_GL_VERSION.major);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, Consts::OPEN_GL_VERSION.minor);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        }

        int flags = 0;

        if (this->initOpenGL)
            flags |= SDL_WINDOW_OPENGL;
        if(this->initVulkan)
            flags |= SDL_WINDOW_VULKAN;

        if(this->initFullscreen)
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if(this->initShown)
            flags |= SDL_WINDOW_SHOWN;
        if(this->initBorderless)
            flags |= SDL_WINDOW_BORDERLESS;
        if(this->initResizable)
            flags |= SDL_WINDOW_RESIZABLE;
        if(this->initMaximized)
            flags |= SDL_WINDOW_MAXIMIZED;
        if(this->initMinimized)
            flags |= SDL_WINDOW_MINIMIZED;

        this->_handle = SDL_CreateWindow(initTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, flags);
        if(this->_handle == nullptr) {
            error_throw(this->logger, "Failed to create SDL window");
        }

        if(this->initOpenGL) {
            this->glContext = SDL_GL_CreateContext(this->_handle);
            if(this->glContext == nullptr) {
                error_throw(this->logger, "Failed to create OpenGL context from SDL window");
            }
        }
    }

    SDL_Window *WindowSDL2::handle() {
        return this->_handle;
    }

    Looper *WindowSDL2::looper(WindowUpdateReceiver* updater) {
        return new WindowSDL2Looper(this, updater);
    }

    void WindowSDL2Looper::loop() {
        // Suspend WindowSDL2, use WindowGLFW

//        if(this->window->initOpenGL) {
//            // OpenGL Loop
//            SDL_Event event;
//
//            bool quit = false;
//            while (!quit) {
//                SDL_GL_SwapWindow(this->window->handle());
//                while (SDL_PollEvent(&event)) {
//                    if(event.type == SDL_QUIT) {
//                        this->receiver->update(true);
//                        if(this->window->shouldQuit) {
//                            quit = true;
//                        }
//                    } else {
//                        this->receiver->update(false);
//                    }
//                }
//            }
//        } else {
//            // No API Loop
//            SDL_Event event;
//
//            bool quit = false;
//            while (!quit) {
//                while (SDL_PollEvent(&event)) {
//                    if(event.type == SDL_QUIT) {
//                        this->receiver->update(true);
//                    } else {
//                        this->receiver->update(false);
//                    }
//                }
//            }
//        }
    }
}