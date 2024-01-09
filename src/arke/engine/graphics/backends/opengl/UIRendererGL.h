#pragma once

#include <arke/engine/graphics/UIRenderer.h>

#include <stack>

namespace Arke {
    class UIRendererGL: public UIRenderer {
    public:
        void render(UI::Element *element) override;

        void drawTexture(UI::DrawCall drawCall);
        void drawText(UI::DrawCall drawCall);
        void drawNinePatch(UI::DrawCall drawCall);
    };
}