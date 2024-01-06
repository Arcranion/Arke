#pragma once

#include "arke/util/Disposable.h"

namespace Arke {
    class Module: public Disposable {
    public:
        virtual void initialize() {};
        virtual void update() {};
    };
}