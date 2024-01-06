#include "Container.h"

namespace Arke::UI {
    void Container::draw(DrawContext* context) {
        context->beginTree();
        for (auto &item: this->elements) {
            item->draw(context);
        }
        context->endTree();
    }

    bool Container::shouldUpdate() {
        return this->_shouldUpdate;
    }

    void Container::flagUpdated() {
        this->_shouldUpdate = false;
    }

    void Container::addElement(Element *element) {
        this->_shouldUpdate = true;
        this->elements.push_back(element);
    }

    std::vector<Element *> Container::getElements() {
        this->_shouldUpdate = true;
        return this->elements;
    }
}