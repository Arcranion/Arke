#pragma once

#include "DrawContext.h"

namespace Arke::UI {
    class Drawable {
    public:
        virtual void draw(DrawContext* context) = 0;
    };
}