#pragma once

#include <arke/util/Disposable.h>

namespace Arke {
    class ResourceContainer: public Disposable {
    public:
        virtual void* resource() = 0;
        void dispose() override = 0;
    };
}