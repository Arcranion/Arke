#include <arke/util/Error.h>

#include <utility>
#include <arke/engine/resources/loaders/TextLoader.h>
#include <arke/engine/resources/loaders/BinaryLoader.h>
#include "Resources.h"

#include <ranges>

#include "loaders/TextureLoader.h"

namespace Arke {
    void Resources::addPath(const std::filesystem::path& path) {
        this->resourcePaths.push_back(path);
    }

    void Resources::removePath(const std::filesystem::path& path) {
        std::erase(this->resourcePaths,path);
    }

    void Resources::addDefaultLoaders() {
        this->addLoader(new TextLoader());
        this->addLoader(new BinaryLoader());
        this->addLoader(new TextureLoader());
    }

    void Resources::addLoader(ResourceLoader *loader) {
        this->resourceLoaders.push_back(loader);
    }

    ResourceLoader *Resources::getLoader(std::string loaderName) {
        if(const auto loader = std::ranges::find_if(this->resourceLoaders, [&loaderName](ResourceLoader* loader) {
            return loader->name() == loaderName;
        }); loader != this->resourceLoaders.end()) {
            return *loader;
        }

        return nullptr;
    }

    void Resources::load(std::string loaderName, std::string path) {
        const auto loader = this->getLoader(loaderName);
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

        for(const auto& root: this->resourcePaths) {
            auto filePath = root / path;
            if (!std::filesystem::is_regular_file(filePath) || !std::filesystem::exists(filePath))
                continue;

            resourceQueue[path] = std::move(loaderName);
            return;
        }

        throw formatted_error("Failed to queue \"{}\" which does not exist", path);
    }

    void Resources::process(const std::chrono::milliseconds duration) {
        const std::chrono::time_point start = std::chrono::system_clock::now();

        auto loaded = std::vector<std::string>();

        for (const auto &[loader, path]: resourceQueue) {
            if(std::chrono::system_clock::now() - start > duration) break;
            this->load(path, loader);
            loaded.emplace_back(loader);
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
        for (const auto &val: this->resources | std::views::values) {
            return val->dispose();
        }

        this->resources.clear();
    }
}
