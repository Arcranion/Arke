#include <glad/gl.h>
#include <arke/util/Error.h>
#include "TextureGL.h"

namespace Arke {

    void TextureGL::create() {
        if(this->_handle != 0)
            dispose();

        glGenTextures(1, &this->_handle);
    }

    void TextureGL::upload(bool freeData) {
        auto glWrapS = convertWrap(wrapS);
        auto glWrapT = convertWrap(wrapT);
        auto glMinFilter = convertFilter(minFilter);
        auto glMagFilter = convertFilter(magFilter);
        auto glChannels = convertChannel(this->data->channels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glMinFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glMagFilter);

        this->bind();

        glTexImage2D(GL_TEXTURE_2D, 0, glChannels, this->size().width, this->size().height, 0, glChannels,
                     GL_UNSIGNED_BYTE, this->data->data);

        if(generateMipmap)
            glGenerateMipmap(GL_TEXTURE_2D);

        if(freeData)
            this->data->dispose();

    }

    void TextureGL::bind() const {
        glBindTexture(GL_TEXTURE_2D, this->_handle);
    }

    void TextureGL::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureGL::dispose() {
        glDeleteTextures(1, &this->_handle);
        this->_handle = 0;
    }

    unsigned int TextureGL::handle() const {
        return this->_handle;
    }

    int TextureGL::convertWrap(Texture::Wrap wrap) {
        switch (wrap) {
            case Wrap::Repeat:
                return GL_REPEAT;
            case Wrap::MirroredRepeat:
                return GL_MIRRORED_REPEAT;
            case Wrap::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
            case Wrap::ClampToBorder:
                return GL_CLAMP_TO_BORDER;
        }
    }

    int TextureGL::convertFilter(Texture::Filter filter) {
        switch (filter) {
            case Filter::Nearest:
                return GL_NEAREST;
            case Filter::Linear:
                return GL_LINEAR;
            case Filter::NearestMipmapNearest:
                return GL_NEAREST_MIPMAP_NEAREST;
            case Filter::LinearMipmapNearest:
                return GL_LINEAR_MIPMAP_NEAREST;
            case Filter::NearestMipmapLinear:
                return GL_NEAREST_MIPMAP_LINEAR;
            case Filter::LinearMipmapLinear:
                return GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    int TextureGL::convertChannel(int channels) {
        switch (channels) {
            case 3:
                return GL_RGB;
            case 4:
                return GL_RGBA;
            default:
                throw formatted_error("Unhandled channel count {}", channels);
        }
    }
}