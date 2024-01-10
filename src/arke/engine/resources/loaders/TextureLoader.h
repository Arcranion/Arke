#pragma once

#include <arke/engine/resources/ResourceLoader.h>
#include <arke/engine/graphics/Texture.h>

namespace Arke {
    using TextureResource = ResourceContainer<Texture>;

    class TextureLoader: public ResourceLoader {
    public:
        std::string name() override;

        ResourceType* load(std::filesystem::path path) override;
    };
}