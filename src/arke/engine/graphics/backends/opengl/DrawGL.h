#pragma once

#include <arke/engine/graphics/VertexAttributes.h>
#include <arke/engine/graphics/Draw.h>

#include <glad/gl.h>

#include <utility>

namespace Arke {
    class DrawGL: public Draw {
    public:
        GLenum primitives = GL_TRIANGLES;
        GLenum usage = GL_STREAM_DRAW;

        VertexAttributes attributes;

        explicit DrawGL(VertexAttributes attributes): attributes(std::move(attributes)) {};
    private:
        unsigned int vertexBufferObject = 0;
        unsigned int elementBufferObject = 0;
        unsigned int vertexArrayObject = 0;

        int verticesLength = 0;
        int indicesLength = 0;

        void initialize() override;
        void begin() override;
        void end() override;
        void draw() override;
        void dispose() override;

        void setVertices(float *vertices, int length) override;
        void setIndices(unsigned int *indices, int length) override;
    };
}