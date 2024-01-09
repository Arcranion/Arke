#include "UIRendererGL.h"

namespace Arke {
    void UIRendererGL::render(UI::Element *element) {
        UI::DrawContext context;
        element->draw(&context);

        auto root = context.getRootNode();

        std::stack<UI::DrawContext::Node*> nodeStack;
        while (!nodeStack.empty()) {
            auto node = nodeStack.top();
            nodeStack.pop();

            if(node->drawCall) {

            } else {
                for (const auto &item: *node->children) {
                    nodeStack.push(item);
                }
            }
        }
    }

    void UIRendererGL::drawTexture(UI::DrawCall drawCall) {
        auto textureId = drawCall.data.textureId;

    }

    void UIRendererGL::drawText(UI::DrawCall drawCall) {

    }

    void UIRendererGL::drawNinePatch(UI::DrawCall drawCall) {

    }
}