#pragma once

#include <vector>
#include <arke/util/Disposable.h>

namespace Arke {
    class ShaderProgram: public Disposable {
    public:
        std::vector<unsigned char> vertexShaderBinary;
        std::vector<unsigned char> fragmentShaderBinary;

        virtual void upload() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}