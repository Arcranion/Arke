#pragma once

#include "Container.h"

namespace Arke::UI {
    /**
     * A container that places child elements in horizontal column.
     */
    class HorizontalContainer: public Container {
        DpSize size() override;
    };
}