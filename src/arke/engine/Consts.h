#pragma once

#include <string>
#include "../util/Version.h"

namespace Arke::Consts {
    const std::string ENGINE_NAME = "Arke";
    const Version ENGINE_VERSION{1, 0, 0};

    const Version OPEN_GL_VERSION{4, 6, 0};

    const int VULKAN_API_VERSION = VK_API_VERSION_1_0;

    const std::vector<const char*> VULKAN_VALIDATION_LAYERS = {
            "VK_LAYER_KHRONOS_validation"
    };

    const bool VULKAN_ENABLE_VALIDATION_LAYER = true;
}