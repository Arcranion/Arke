#include "Core.h"

namespace Arke {
    Application *Core::application() {
        return Application::instance();
    }

    Graphics *Core::graphics() {
        return application()->graphics;
    }

    Factory *Core::factory() {
        return graphics()->factory();
    }

    Window *Core::window() {
        return graphics()->window;
    }

    ModuleMain *Core::main() {
        return application()->main;
    }


}