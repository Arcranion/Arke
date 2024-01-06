#pragma once

#include <arke/engine/graphics/ShaderProgram.h>
#include <arke/util/Logging.h>

#include "glad/gl.h"

using namespace util;

namespace Arke {
    class ShaderProgramGL: public ShaderProgram {
    private:
        logger_t logger = create_logger("ShaderProgramGL");

        unsigned int _handle;
    public:
        static unsigned int createShader(
                GLenum shaderType,
                std::vector<unsigned char> shaderBinary
        );

        static void compileShader(unsigned int shader, const std::string& shaderEntrypoint = "main");

        static unsigned int makeProgram(unsigned int vertexShader, unsigned int fragmentShader);

        void upload() override;
        void bind() override;
        void unbind() override;
        void dispose() override;
    };
}