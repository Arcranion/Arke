#include "HorizontalContainer.h"

namespace Arke::UI {
    DpSize HorizontalContainer::size() {
        Dp maxWidth = 0;
        Dp heightSum = 0;
        for (const auto &item: this->elements) {
            auto itemSize = item->size();
            heightSum += itemSize.height;
            if (maxWidth < itemSize.width)
                maxWidth = itemSize.width;
        }

        return { maxWidth, heightSum };
    }
}