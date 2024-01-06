#pragma once

#include <stdexcept>
#include "spdlog/fmt/bundled/core.h"

namespace util {
    template<typename... T>
    [[nodiscard]] inline auto formatted_error(fmt::format_string<T...> fmt, T&&... args) -> std::runtime_error {
        return std::runtime_error(fmt::vformat(fmt, fmt::make_format_args(args...)));
    }

    template<typename... T>
    [[nodiscard]] inline auto not_implemented_error(fmt::format_string<T...> fmt, T&&... args) -> std::runtime_error {
        auto formatted = fmt::vformat(fmt, fmt::make_format_args(args...));
        if(formatted != "") formatted = ": " + formatted;

        return std::runtime_error("This operation is not implemented" + formatted);
    }

    [[nodiscard]] inline auto not_implemented_error() -> std::runtime_error {
        return std::runtime_error("This operation is not implemented");
    }
}