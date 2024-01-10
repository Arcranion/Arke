#include "Application.h"

namespace Arke {
    Application* Application::_instance;

    Application::Application() {
        Application::_instance = this;
    }

    void Application::launch() {
        this->logger->info("Launching");

        // Abort if graphics was not initialized successfully
        if(!this->graphics->available()) {
            this->logger->error("Graphics is not available");
            return;
        }

        try {
            this->main->initialize();
        } catch (const std::exception& e) {
            this->logger->critical("Exception while initializing main: {}", e.what());
            return;
        }

        auto updater = new ApplicationUpdater(this);
        auto looper = this->window()->looper(updater);
        looper->loop();

        // Clean up
        delete looper;
        delete updater;

        // Dispose all
        this->main->dispose();
        this->graphics->dispose();
    }

    Window *Application::window() const {
        return this->graphics->window;
    }

    Application *Application::instance() {
        return Application::_instance;
    }

    bool Application::ApplicationUpdater::shouldClose() {
        return this->application->main->shouldCloseWindow();
    }

    void Application::ApplicationUpdater::update() {
        this->application->main->update();
    }

    void Application::ApplicationUpdater::resize(Arke::IntSize size) {
        this->application->graphics->updateViewport(size);
        this->application->main->resize(size);

        this->update();
    }
}