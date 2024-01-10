#include <stb/stb_image.h>
#include <arke/engine/application/Core.h>
#include "Texture.h"

namespace Arke {
    Texture* Texture::load(const std::filesystem::path& path) {
        auto data = Texture::loadData(path);
        return Core::factory()->newTexture(data);
    }

    Texture::Data *Texture::loadData(const std::filesystem::path& path) {
        IntSize size;
        int channels;

        auto data = stbi_load(path.string().c_str(), &size.width, &size.height, &channels, 0);

        auto object = new Data;
        object->data = data;
        object->size = size;
        object->channels = channels;

        return object;
    }

    void Texture::Data::dispose() {
        stbi_image_free(data);
    }
}