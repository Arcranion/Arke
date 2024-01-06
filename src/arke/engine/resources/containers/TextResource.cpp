#include "TextResource.h"

namespace Arke {
    void *TextResource::resource() {
        return this->data;
    }

    void TextResource::dispose() {
        delete this->data;
    }
}