#pragma once

#include <arke/engine/graphics/Factory.h>

namespace Arke {
    class FactoryGL: public Factory {
        ShaderProgram* newShaderProgram() override;
        Draw* newDraw(Arke::VertexAttributes attributes) override;
        Texture* newTexture(Texture::Data *data) override;
    };
}