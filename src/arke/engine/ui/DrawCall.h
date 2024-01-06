#pragma once

#include <arke/engine/ui/unit/Dp2.h>

#include <string>

namespace Arke::UI {
    class DrawCall {
        /**
         * Offset from parent draw call in pixels
         */
        Int2 offset;
        Int2 size;

        // +8 bytes using union
        union {
            struct TextData {
                std::string* text;
                int fontIndex;
            } textData;

            unsigned int textureId;

            // TODO Nine-patch
        };

        /**
         * Should implement calls for text, texture and nine-patch texture draw
         */
        enum Type {
            Texture,
            NinePatch, // TODO Unused yet
            Text
        } type = Texture;
    };
}