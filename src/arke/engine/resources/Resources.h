#pragma once

#include <vector>
#include <string>
#include <map>
#include "ResourceLoader.h"
#include <arke/util/Logging.h>
#include <iostream>

using namespace util;

namespace Arke {
    class Resources: Disposable {
    private:
        logger_t logger = create_logger("Resources");

        std::vector<std::filesystem::path> resourcePaths;
        std::vector<ResourceLoader*> resourceLoaders;
        std::map<std::string, std::string> resourceQueue;
        std::map<std::string, ResourceContainer*> resources;

        int remaining = 0;
    public:
        void addPath(const std::filesystem::path& path);
        void removePath(const std::filesystem::path& path);

        void addDefaultLoaders();
        void addLoader(ResourceLoader* loader);
        ResourceLoader* getLoader(std::string loaderName);

        template<typename T>
        inline T* get(const std::string& path);

        template<typename T>
        inline T getData(const std::string& path);

        template<typename T>
        inline ResourceContainer* getContainer(const std::string& path);


        void load(std::string loaderName, std::string path);
        void queue(std::string loaderName, const std::string& path);

        void process(std::chrono::milliseconds duration);

        [[nodiscard]] bool loadFinished() const;
        [[nodiscard]] int remainingQueue() const;

        void dispose() override;
    };

    template<typename T>
    T* Resources::get(const std::string& path) {
        return reinterpret_cast<T*>(resources[path]->resource());
    }

    template<typename T>
    T Resources::getData(const std::string &path) {
        return *this->get<T>(path);
    }

    template<typename T>
    ResourceContainer *Resources::getContainer(const std::string &path) {
        return resources[path];
    }
}