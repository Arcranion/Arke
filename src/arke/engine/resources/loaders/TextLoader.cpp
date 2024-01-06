#include <arke/util/Error.h>
#include <arke/engine/resources/containers/TextResource.h>
#include "TextLoader.h"

namespace Arke {
    std::string TextLoader::name() {
        return "TextLoader";
    }

    ResourceContainer* TextLoader::load(std::filesystem::path path) {
        std::ifstream stream(path);

        if(!stream.is_open()) {
            throw formatted_error("Input file stream is not opened for path \"{}\"", path.string());
        }

        auto* content = new std::string();
        stream >> *content;

        stream.close();

        return new TextResource(content);
    }
}