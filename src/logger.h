/**
 * @file logger.h
 * @brief Logging utilities using spdlog
 *
 * This file demonstrates using external dependencies managed by vcpkg.
 * spdlog is a fast C++ logging library.
 *
 * @author Your Name
 * @date 2026-01-05
 * @version 1.0.0
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <spdlog/spdlog.h>

/**
 * @namespace mathlib
 * @brief Mathematical operations namespace
 */
namespace mathlib {

/**
 * @class Logger
 * @brief Wrapper around spdlog for mathematical library logging
 *
 * Provides convenient logging functions for the mathlib library.
 * Uses spdlog (installed via vcpkg) as the underlying logging framework.
 *
 * @par Example:
 * @code
 * Logger::info("Computing square of {}", 5.0);
 * Logger::warn("Large value detected: {}", 1e100);
 * Logger::error("Invalid input: {}", -1);
 * @endcode
 */
class Logger {
  public:
    /**
     * @brief Initialize the logger
     * @param level Logging level (trace, debug, info, warn, error, critical)
     */
    static void init(spdlog::level::level_enum level = spdlog::level::info);

    /**
     * @brief Log an info message
     * @param format Format string (fmt library syntax)
     * @param args Arguments to format
     */
    template <typename... Args>
    static void info(fmt::format_string<Args...> format, Args&&... args) {
        spdlog::info(format, std::forward<Args>(args)...);
    }

    /**
     * @brief Log a warning message
     * @param format Format string (fmt library syntax)
     * @param args Arguments to format
     */
    template <typename... Args>
    static void warn(fmt::format_string<Args...> format, Args&&... args) {
        spdlog::warn(format, std::forward<Args>(args)...);
    }

    /**
     * @brief Log an error message
     * @param format Format string (fmt library syntax)
     * @param args Arguments to format
     */
    template <typename... Args>
    static void error(fmt::format_string<Args...> format, Args&&... args) {
        spdlog::error(format, std::forward<Args>(args)...);
    }

    /**
     * @brief Log a debug message
     * @param format Format string (fmt library syntax)
     * @param args Arguments to format
     */
    template <typename... Args>
    static void debug(fmt::format_string<Args...> format, Args&&... args) {
        spdlog::debug(format, std::forward<Args>(args)...);
    }
};

}  // namespace mathlib

#endif  // LOGGER_H