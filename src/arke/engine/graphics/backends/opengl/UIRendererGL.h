#pragma once

#include <arke/engine/graphics/UIRenderer.h>

namespace Arke {
    class UIRendererGL: public UIRenderer {
    public:
        void render(UI::Element *element) override;
    };
}