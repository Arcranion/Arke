#pragma once

#include <arke/engine/math/unit/Size.h>
#include <arke/util/Disposable.h>
#include <filesystem>

namespace Arke {
    class Texture: public Disposable {
    public:
        enum class Wrap;
        enum class Filter;
        struct Data;
    protected:
        IntSize _size = {};
    public:
        Wrap wrapS = Wrap::Repeat;
        Wrap wrapT = Wrap::Repeat;
        Filter minFilter = Filter::Nearest;
        Filter magFilter = Filter::Nearest;

        bool generateMipmap = false;

        [[nodiscard]] inline IntSize size() const {
            return this->_size;
        }

        virtual void create() = 0;

        virtual void upload(bool freeData) = 0;
        virtual void upload() { this->upload(true); }

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static Texture* load(const std::filesystem::path& path);
        static Data* loadData(const std::filesystem::path& path);

        virtual ~Texture() = default;

        struct Data: public Disposable {
        public:
            unsigned char* data = nullptr;

            IntSize size = {};
            int channels = 0;

            void dispose() override;
        };

        enum class Wrap {
            Repeat,
            MirroredRepeat,
            ClampToEdge,
            ClampToBorder
        };

        enum class Filter {
            Nearest,
            Linear,
            NearestMipmapNearest,
            LinearMipmapNearest,
            NearestMipmapLinear,
            LinearMipmapLinear
        };
    };
}