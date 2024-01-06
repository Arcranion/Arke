#pragma once

#include "arke/engine/graphics/Graphics.h"
#include "ModuleMain.h"
#include "arke/util/Logging.h"
#include "arke/engine/graphics/Window.h"

#undef main

using namespace util;

namespace Arke {
    class Application {
    private:
        logger_t logger = create_logger("Application");

        static Application* _instance;
    public:
        Application();

        Graphics* graphics = nullptr;
        ModuleMain* main = nullptr;

        void launch();

        [[nodiscard]] Window* window() const;

        static Application* instance();
    private:
        class ApplicationUpdater: public WindowUpdateReceiver {
        public:
            Application* application = nullptr;

            explicit ApplicationUpdater(Application* application): application(application) {};

            bool shouldClose() override;
            void update() override;
            void resize(Arke::IntSize size) override;
        };
    };
}