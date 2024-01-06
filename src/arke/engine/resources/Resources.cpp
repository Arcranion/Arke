#include <arke/util/Error.h>

#include <utility>
#include <arke/engine/resources/loaders/TextLoader.h>
#include <arke/engine/resources/loaders/BinaryLoader.h>
#include "Resources.h"

namespace Arke {
    void Resources::addPath(const std::filesystem::path& path) {
        this->resourcePaths.push_back(path);
    }

    void Resources::removePath(const std::filesystem::path& path) {
        this->resourcePaths.erase(std::remove(this->resourcePaths.begin(), this->resourcePaths.end(),path), this->resourcePaths.end());
    }

    void Resources::addDefaultLoaders() {
        this->addLoader(new TextLoader());
        this->addLoader(new BinaryLoader());
    }

    void Resources::addLoader(ResourceLoader *loader) {
        this->resourceLoaders.push_back(loader);
    }

    ResourceLoader *Resources::getLoader(std::string loaderName) {
        auto loader = std::find_if(this->resourceLoaders.begin(), this->resourceLoaders.end(), [&loaderName](ResourceLoader* loader) {
            return loader->name() == loaderName;
        });

        if(loader != this->resourceLoaders.end()) {
            return *loader;
        } else {
            return nullptr;
        }
    }

    void Resources::load(std::string loaderName, std::string path) {
        auto loader = this->getLoader(loaderName);
        if(!loader) {
            throw formatted_error("Loader named \"{}\" not found", loaderName);
        }

        for(const auto& root: this->resourcePaths) {
            auto filePath = root / path;
            if (!std::filesystem::is_regular_file(filePath) || !std::filesystem::exists(filePath))
                continue;

            this->logger->info("Loading {}", path);
            this->resources[path] = loader->load(filePath);
            return;
        }

        throw formatted_error("Failed to find resource named \"{}\"", path);
    }

    void Resources::queue(std::string loaderName, const std::string& path) {
        this->remaining++;

        resourceQueue[path] = std::move(loaderName);
    }

    void Resources::process(std::chrono::milliseconds duration) {
        std::chrono::time_point start = std::chrono::system_clock::now();

        auto loaded = std::vector<std::string>();

        for (const auto &item: resourceQueue) {
            if(std::chrono::system_clock::now() - start > duration) break;
            this->load(item.second, item.first);
            loaded.emplace_back(item.first);
            this->remaining--;
        }

        for (const auto &item: loaded) {
            this->resourceQueue.erase(resourceQueue.find(item));
        }
    }

    bool Resources::loadFinished() const {
        return this->remaining == 0;
    }

    int Resources::remainingQueue() const {
        return this->remaining;
    }

    void Resources::dispose() {
        for (const auto &item: this->resources) {
            return item.second->dispose();
        }

        this->resources.clear();
    }
}