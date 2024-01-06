#include "GraphicsGL.h"

namespace Arke {
    void GraphicsGL::initialize() {
        if(!gladLoadGL((GLADloadfunc) window->glLoadProc())) {
            error_throw(this->logger, "Failed to initialize GLAD");
        }

        this->_factory = new FactoryGL();

        updateViewport({ window->size().width, window->size().height });
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        this->_available = true;
    }

    void GraphicsGL::dispose() {
        this->_available = false;
    }

    bool GraphicsGL::available() {
        return this->_available;
    }

    void GraphicsGL::updateViewport(Arke::IntSize size) {
        glViewport(0, 0, size.width, size.height);
    }

    void GraphicsGL::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    Factory* GraphicsGL::factory() {
        return this->_factory;
    }
}
