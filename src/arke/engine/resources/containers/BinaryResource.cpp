#include "BinaryResource.h"

namespace Arke {
    void *BinaryResource::resource() {
        return this->data;
    }

    void BinaryResource::dispose() {
        delete this->data;
    }
}