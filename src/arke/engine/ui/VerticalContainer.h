#pragma once

#include "Container.h"

namespace Arke::UI {
    /**
     * A container that places child elements in vertical row.
     */
    class VerticalContainer: public Container {
        DpSize size() override;
    };
}