#pragma once

#include <arke/util/Disposable.h>

namespace Arke {
    class ResourceType: public Disposable {
    protected:
        void* data = nullptr;
    public:
        void* resource() {
            return this->data;
        };
    };

    template<class T = void>
    class ResourceContainer: public ResourceType {
    public:
        explicit inline ResourceContainer(T* data) {
            this->data = data;
        };

        void dispose() override {
            delete (T*) this->data;
        }
    };
}