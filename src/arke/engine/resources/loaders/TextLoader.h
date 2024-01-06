#pragma once

#include <fstream>

#include <arke/engine/resources/ResourceLoader.h>

using namespace util;

namespace Arke {
    class TextLoader: public ResourceLoader {
        std::string name() override;

        ResourceContainer* load(std::filesystem::path path) override;
    };
}