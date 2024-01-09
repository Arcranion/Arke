#include "FactoryGL.h"
#include "ShaderProgramGL.h"
#include "DrawGL.h"
#include "TextureGL.h"

namespace Arke {
    ShaderProgram* FactoryGL::newShaderProgram() {
        return new ShaderProgramGL();
    }

    Draw* FactoryGL::newDraw(Arke::VertexAttributes attributes) {
        return new DrawGL(attributes);
    }

    Texture* FactoryGL::newTexture(Texture::Data *data) {
        return new TextureGL(data);
    }
}