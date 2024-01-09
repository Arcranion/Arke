#pragma once

#include <arke/engine/resources/ResourceLoader.h>
#include <arke/util/Error.h>

#include <fstream>
#include <utility>
#include <iterator>

using namespace util;

namespace Arke {
    using BinaryResource = ResourceContainer<std::vector<unsigned char>>;

    class BinaryLoader: public ResourceLoader {
        std::string name() override;

        ResourceType* load(std::filesystem::path path) override;
    };
}