#pragma once

#include <arke/engine/resources/ResourceContainer.h>
#include <string>

namespace Arke {
    class TextResource: public ResourceContainer {
    public:
        std::string* data;

        void* resource() override;
        void dispose() override;

        explicit TextResource(std::string* data): data(data) {}
    };
}