#pragma once

#include <arke/engine/graphics/Graphics.h>
#include "Application.h"

namespace Arke {
    class Core {
    public:
        static Application* application();
        static Graphics* graphics();
        static Factory* factory();
        static Window* window();
        static ModuleMain* main();
    };
}