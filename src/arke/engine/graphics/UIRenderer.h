#pragma once

#include <arke/engine/ui/Element.h>

namespace Arke {
    class UIRenderer {
    public:
        virtual void render(UI::Element *element) = 0;
    };
}