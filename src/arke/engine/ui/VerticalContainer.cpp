#include "VerticalContainer.h"

namespace Arke::UI {

    DpSize VerticalContainer::size() {
        Dp maxHeight = 0;
        Dp widthSum = 0;
        for (const auto &item: this->elements) {
            auto itemSize = item->size();
            widthSum += itemSize.width;
            if (maxHeight < itemSize.height)
                maxHeight = itemSize.height;
        }

        return { widthSum, maxHeight };
    }
}