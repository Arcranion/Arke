#pragma once

#include <arke/engine/math/unit/Size.h>

namespace Arke {
    class Looper {
    public:
        virtual void loop() {};
    };

    class WindowUpdateReceiver {
    public:
        virtual bool shouldClose() { return true; };
        virtual void update() {};
        virtual void resize(IntSize size) {};
    };
}