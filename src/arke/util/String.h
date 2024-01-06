#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

namespace util {
    std::vector<const char *> to_c_str(std::vector<std::string> vector) {
        std::vector<const char*> c_strs;
        std::transform(vector.begin(), vector.end(), std::back_inserter(c_strs), [](const std::string& name) {
            return name.c_str();
        });
        return c_strs;
    }
}