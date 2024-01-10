#pragma once

#include <arke/engine/graphics/Texture.h>

using namespace util;

namespace Arke {
    class TextureGL: public Texture {
    private:
        Data* data = nullptr;

        unsigned int _handle = 0;
    public:
        explicit TextureGL(Data* data): data(data) {
            this->_size = data->size;
        };

        ~TextureGL() override = default;

        void create() override;

        void upload(bool freeData) override;

        void bind() const;
        void unbind() const;

        void dispose() override;

        [[nodiscard]] unsigned int handle() const;
    private:
        static int convertWrap(Wrap wrap);
        static int convertFilter(Filter filter);
        static int convertChannel(int channels);
    };
}