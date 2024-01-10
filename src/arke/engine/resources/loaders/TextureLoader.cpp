#include "TextureLoader.h"

namespace Arke {
    std::string TextureLoader::name() {
        return "TextureLoader";
    }

    ResourceType* TextureLoader::load(std::filesystem::path path) {
        return new TextureResource(Texture::load(path));
    }
}

