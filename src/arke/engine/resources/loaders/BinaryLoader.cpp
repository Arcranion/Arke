#include <iostream>
#include "BinaryLoader.h"

namespace Arke {
    std::string BinaryLoader::name() {
        return "BinaryLoader";
    }

    ResourceContainer* BinaryLoader::load(std::filesystem::path path) {
        std::ifstream inStream(path, std::ios::binary);

        if(!inStream.is_open()) {
            throw formatted_error("Input file stream is not opened for path \"{}\"", path.string());
        }

        auto buffer = new std::vector<unsigned char>(std::istreambuf_iterator<char>(inStream), {});

        return new BinaryResource(buffer);
    }
}