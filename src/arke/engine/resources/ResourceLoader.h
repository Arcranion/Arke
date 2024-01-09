#pragma once

#include <string>
#include <filesystem>
#include <utility>
#include <arke/util/Disposable.h>
#include "ResourceType.h"

namespace Arke {
    class ResourceLoader: Disposable {
    public:
        virtual std::string name() = 0;

        virtual ResourceType* load(std::filesystem::path path) = 0;
    };
}