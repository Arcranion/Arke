#pragma once

#include "arke/util/Disposable.h"
#include "arke/engine/math/unit/Size.h"
#include "Window.h"
#include "Factory.h"

namespace Arke {
    class Graphics: public Disposable {
    public:
        Window* window = nullptr;

        virtual void initialize() = 0;
        virtual bool available() = 0;

        virtual void updateViewport(IntSize size) = 0;
        virtual void clear() = 0;

        virtual Factory* factory() = 0;
    };
}