#pragma once

#include <arke/engine/resources/ResourceContainer.h>
#include <vector>

namespace Arke {
    class BinaryResource: public ResourceContainer {
    public:
        std::vector<uint8_t>* data;

        explicit BinaryResource(std::vector<uint8_t>* data): data(data) {};

        void* resource() override;
        void dispose() override;
    };
}