#include "DrawGL.h"

namespace Arke {
    void DrawGL::initialize() {
        // Generate vertex buffer object
        glGenBuffers(1, &this->vertexBufferObject);

        // Generate element buffer object
        glGenBuffers(1, &this->elementBufferObject);

        // Generate vertex array object
        glGenVertexArrays(1, &this->vertexArrayObject);

        glBindVertexArray(this->vertexArrayObject);
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);

            // Configure attributes
            {
                int offset = 0, index = 0;
                for (const auto& attribute : this->attributes.list) {
                    GLenum glType;
                    switch (attribute.type) {
                        case VertexAttribute::Type::Float:
                            glType = GL_FLOAT;
                            break;
                        case VertexAttribute::Type::UnsignedByte:
                            glType = GL_UNSIGNED_BYTE;
                            break;
                        case VertexAttribute::Type::UnsignedShort:
                            glType = GL_UNSIGNED_SHORT;
                            break;
                    }
                    glVertexAttribPointer(
                            index,
                            attribute.components,
                            glType,
                            attribute.normalized,
                            this->attributes.totalSizeInBytes(),
                            reinterpret_cast<void*>(offset)
                    );

                    offset += attribute.sizeInBytes();

                    glEnableVertexAttribArray(index);

                    index++;
                }
            }
        }
        glBindVertexArray(0);
    }

    void DrawGL::begin() {

    }

    void DrawGL::end() {

    }

    void DrawGL::draw() {
        glBindVertexArray(this->vertexArrayObject);
        {
            // Draw
//            glDrawArrays(this->primitives, 0, this->indicesLength);
            glDrawElements(this->primitives, this->indicesLength, GL_UNSIGNED_INT, nullptr);
        }
        glBindVertexArray(0);
    }

    void DrawGL::dispose() {
        glDeleteVertexArrays(1, &this->vertexArrayObject);
        glDeleteBuffers(1, &this->vertexBufferObject);
        glDeleteBuffers(1, &this->elementBufferObject);

        this->vertexArrayObject = 0;
        this->vertexBufferObject = 0;
        this->elementBufferObject = 0;
    }

    void DrawGL::setVertices(float *vertices, int length) {
        // Update vertices
        this->verticesLength = length;

        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, length, vertices, this->usage);
    }

    void DrawGL::setIndices(unsigned int *indices, int length) {
        // Update indices
        this->indicesLength = length;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, indices, this->usage);
    }
}