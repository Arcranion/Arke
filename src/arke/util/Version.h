#pragma once

#include "vulkan/vulkan.h"

struct Version {
    int major;
    int minor;
    int patch;

    [[nodiscard]] unsigned int vkMakeVersion() const {
        return VK_MAKE_VERSION(major, minor, patch);
    }
};