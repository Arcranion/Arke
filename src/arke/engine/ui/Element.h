#pragma once

#include <arke/engine/ui/unit/Dp2.h>
#include <arke/engine/ui/unit/DpSize.h>
#include "Drawable.h"

namespace Arke::UI {
    class Element: public Drawable {
    public:
        virtual bool shouldUpdate() = 0;
        virtual void flagUpdated() = 0;

        virtual DpSize size() = 0;
        virtual Dp2 offset() = 0;
    };
}