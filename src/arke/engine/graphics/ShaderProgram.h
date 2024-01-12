#pragma once

#include <vector>
#include <arke/util/Disposable.h>
#include <GL/gl.h>

namespace Arke {
    class ShaderProgram: public Disposable {
    public:
        std::vector<unsigned char> vertexShaderBinary;
        std::vector<unsigned char> fragmentShaderBinary;

        virtual void upload() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void uniform1f(int location, float v0) = 0;
        virtual void uniform2f(int location, float v0, float v1) = 0;
        virtual void uniform3f(int location, float v0, float v1, float v2) = 0;
        virtual void uniform4f(int location, float v0, float v1, float v3) = 0;

        virtual void uniform1i(int location, int v0) = 0;
        virtual void uniform2i(int location, int v0, int v1) = 0;
        virtual void uniform3i(int location, int v0, int v1, int v2) = 0;
        virtual void uniform4i(int location, int v0, int v1, int v2, int v3) = 0;

        virtual void uniform1ui(int location, unsigned int v0) = 0;
        virtual void uniform2ui(int location, unsigned int v0, unsigned int v1) = 0;
        virtual void uniform3ui(int location, unsigned int v0, unsigned int v1, unsigned int v2) = 0;
        virtual void uniform4ui(int location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) = 0;

        virtual void uniform1fv(int location, int count, const float* value) = 0;
        virtual void uniform2fv(int location, int count, const float* value) = 0;
        virtual void uniform3fv(int location, int count, const float* value) = 0;
        virtual void uniform4fv(int location, int count, const float* value) = 0;

        virtual void uniform1iv(int location, int count, const int* value) = 0;
        virtual void uniform2iv(int location, int count, const int* value) = 0;
        virtual void uniform3iv(int location, int count, const int* value) = 0;
        virtual void uniform4iv(int location, int count, const int* value) = 0;

        virtual void uniform1uiv(int location, int count, const unsigned int* value) = 0;
        virtual void uniform2uiv(int location, int count, const unsigned int* value) = 0;
        virtual void uniform3uiv(int location, int count, const unsigned int* value) = 0;
        virtual void uniform4uiv(int location, int count, const unsigned int* value) = 0;

        virtual void uniformMatrix2fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix3fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix4fv(int location, int count, bool transpose, const float* value) = 0;

        virtual void uniformMatrix2x3fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix3x2fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix2x4fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix4x2fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix3x4fv(int location, int count, bool transpose, const float* value) = 0;
        virtual void uniformMatrix4x3fv(int location, int count, bool transpose, const float* value) = 0;
    };
}
