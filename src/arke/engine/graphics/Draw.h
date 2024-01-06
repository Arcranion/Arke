#pragma once

#include <vector>
#include <arke/util/Disposable.h>

namespace Arke {
    /**
     * Interface that draws vertices/indices
     */
    class Draw: public Disposable {
    public:
        virtual void initialize() = 0;
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual void draw() = 0;

        virtual void setVertices(float* vertices, int length) = 0;
        virtual void setIndices(unsigned int* indices, int length) = 0;

        virtual void setVertices(std::vector<float> vertices) {
            this->setVertices(vertices.data(), static_cast<int>(sizeof(float) * vertices.size()));
        }

        virtual void setIndices(std::vector<unsigned int> indices) {
            this->setIndices(indices.data(), static_cast<int>(sizeof(unsigned int) * indices.size()));
        }
    };
}