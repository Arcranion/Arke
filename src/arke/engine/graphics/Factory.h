#pragma once

#include "ShaderProgram.h"
#include "Draw.h"
#include "VertexAttributes.h"

namespace Arke {
    class Factory {
    public:
        virtual ShaderProgram* newShaderProgram() = 0;
        virtual Draw* newDraw(Arke::VertexAttributes attributes) = 0;
    };
}