#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace util {
    using logger_t = std::shared_ptr<spdlog::logger>;

    inline logger_t create_logger(const std::string& name) {
        return spdlog::stdout_color_mt(name);
    }

    /**
    * Log error and throw std::runtime_exception with message
    */
    template<typename... Args>
    inline void error_throw(logger_t logger, fmt::format_string<Args...> fmt, Args &&...args) {
        auto formatted = fmt::format(fmt, args...);
        logger->error(formatted);
        throw std::runtime_error(formatted);
    }
}