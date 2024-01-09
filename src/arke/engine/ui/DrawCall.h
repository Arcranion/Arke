#pragma once

#include <arke/engine/ui/unit/Dp2.h>

#include <string>

namespace Arke::UI {
    class DrawCall {
    public:
        struct TextData {
            std::string* text;
            int fontIndex;
        };

        enum class Type {
            Texture,
            NinePatch, // TODO Unused yet
            Text
        };

        /**
         * Offset from parent draw call in pixels
         */
        Int2 offset;
        Int2 size;

        // +8 bytes using union
        union {
            TextData text{};

            unsigned int textureId;

            // TODO Nine-patch
        } data;

        /**
         * Should implement calls for text, texture and nine-patch texture draw
         */
        Type const type;

        explicit DrawCall(unsigned int textureId): type(Type::Texture) {
            this->data.textureId;
        }

        explicit DrawCall(TextData data): type(Type::Text) {
            this->data.text;
        };
    };
}