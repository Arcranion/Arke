#pragma once

#include <string>
#include <filesystem>
#include <utility>
#include <arke/util/Disposable.h>
#include "ResourceContainer.h"

namespace Arke {
    class ResourceLoader: Disposable {
    public:
        virtual std::string name() = 0;

        virtual ResourceContainer* load(std::filesystem::path path) = 0;
    };
}