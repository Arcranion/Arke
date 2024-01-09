#pragma once

#include <fstream>

#include <arke/engine/resources/ResourceLoader.h>

using namespace util;

namespace Arke {
    using TextResource = ResourceContainer<std::string>;

    class TextLoader: public ResourceLoader {
        std::string name() override;

        ResourceType* load(std::filesystem::path path) override;
    };
}