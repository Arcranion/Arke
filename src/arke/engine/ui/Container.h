#pragma once

#include <vector>

#include "Drawable.h"

#include "arke/util/TypeCheck.h"
#include "Element.h"

namespace Arke::UI {
    /**
     * A container with no layout flow.
     */
    class Container: public Element {
    protected:
        bool _shouldUpdate = true;

        std::vector<Element*> elements;

        void draw(DrawContext* context) override;

        bool shouldUpdate() override;
        void flagUpdated() override;

        virtual void addElement(Element* element);
        virtual std::vector<Element*> getElements();
    };
}