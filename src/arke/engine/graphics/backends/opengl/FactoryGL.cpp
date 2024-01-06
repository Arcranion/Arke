#include "FactoryGL.h"
#include "ShaderProgramGL.h"
#include "DrawGL.h"

namespace Arke {
    ShaderProgram* FactoryGL::newShaderProgram() {
        return new ShaderProgramGL();
    }

    Draw* FactoryGL::newDraw(Arke::VertexAttributes attributes) {
        return new DrawGL(attributes);
    }
}