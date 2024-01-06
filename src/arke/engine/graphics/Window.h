#pragma once

#include <string>
#include <vector>
#include "arke/engine/math/unit/Size.h"
#include "vulkan/vulkan.h"
#include "Looper.h"

namespace Arke {
    class Window {
    public:
        /////////////////////////////
        // Graphics
        /////////////////////////////

        virtual std::vector<std::string> vkRequiredExtensions() = 0;
        virtual VkSurfaceKHR vkCreateSurface(VkInstance vkInstance) = 0;

        virtual void* glLoadProc() = 0;
        /////////////////////////////
        // Object
        /////////////////////////////
        virtual Looper* looper(WindowUpdateReceiver* updater) = 0;

        virtual IntSize size() = 0;
    };
}