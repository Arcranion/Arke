#pragma once

#include "Module.h"

namespace Arke {
    class ModuleMain: public Module {
    public:
        virtual bool shouldCloseWindow() {
            return false;
        };

        virtual void resize(IntSize size) {};
    };
}