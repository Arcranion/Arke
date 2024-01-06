#pragma once

#include "arke/engine/graphics/Graphics.h"
#include "arke/util/Logging.h"

#include "SDL2/SDL.h"
#include "glad/gl.h"
#include "arke/engine/graphics/Window.h"
#include "FactoryGL.h"

using namespace util;

namespace Arke {
    class GraphicsGL: public Graphics {
    private:
        logger_t logger = create_logger("GraphicsGL");

        bool _available = false;

        FactoryGL* _factory;
    public:
        void initialize() override;
        void dispose() override;
        bool available() override;

        void updateViewport(Arke::IntSize size) override;
        void clear() override;

        Factory* factory() override;
    };
}