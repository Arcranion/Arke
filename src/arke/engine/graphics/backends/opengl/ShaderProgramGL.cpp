#include <string>
#include <stdexcept>
#include <arke/util/Error.h>
#include <iostream>
#include "ShaderProgramGL.h"


namespace Arke {
    unsigned int ShaderProgramGL::createShader(
            GLenum shaderType,
            std::vector<unsigned char> shaderBinary
    ) {
        auto shader = glCreateShader(shaderType);
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderBinary.data(),
                       static_cast<int>(shaderBinary.size()));
        return shader;
    }

    void ShaderProgramGL::compileShader(unsigned int shader, const std::string& shaderEntrypoint) {
        glSpecializeShader(shader, shaderEntrypoint.c_str(), 0, nullptr, nullptr);

        int isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE) {
            int length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> log(length);
            glGetShaderInfoLog(shader, length, &length, log.data());

            throw std::runtime_error(std::string(log.begin(), log.end()));
        }
    }

    unsigned int ShaderProgramGL::makeProgram(unsigned int vertexShader, unsigned int fragmentShader) {
        auto program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        int isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if(isLinked == GL_FALSE) {
            int length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> log(length);
            glGetProgramInfoLog(program, length, &length, log.data());

            glDeleteProgram(program);

            throw std::runtime_error(std::string(log.begin(), log.end()));
        }

        return program;
    }

    void ShaderProgramGL::upload() {
        auto vertexShader = createShader(GL_VERTEX_SHADER, this->vertexShaderBinary);
        auto fragmentShader = createShader(GL_FRAGMENT_SHADER, this->fragmentShaderBinary);

        // Compile vertex shader
        try {
            compileShader(vertexShader);
        } catch(const std::runtime_error& error) {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            throw formatted_error("Failed to compile vertex shader: {}", error.what());
        }

        // Compile fragment shader
        try {
            compileShader(fragmentShader);
        } catch(const std::runtime_error& error) {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            throw formatted_error("Failed to compile fragment shader: {}", error.what());
        }

        // Link program
        try {
            this->_handle = makeProgram(vertexShader, fragmentShader);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        } catch(const std::runtime_error& error) {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            throw formatted_error("Failed to link program: {}", error.what());
        }
    }

    void ShaderProgramGL::bind() {
        glUseProgram(this->_handle);
    }

    void ShaderProgramGL::unbind() {
        glUseProgram(0);
    }

    void ShaderProgramGL::dispose() {
        glDeleteProgram(this->_handle);
    }
}