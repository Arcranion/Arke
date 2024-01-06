#pragma once

#include <arke/engine/resources/ResourceLoader.h>
#include <arke/util/Error.h>
#include <arke/engine/resources/containers/BinaryResource.h>

#include <fstream>
#include <utility>
#include <iterator>

using namespace util;

namespace Arke {
    class BinaryLoader: public ResourceLoader {
        std::string name() override;

        ResourceContainer* load(std::filesystem::path path) override;
    };
}