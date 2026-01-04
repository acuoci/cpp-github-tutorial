/**
 * @file logger.cpp
 * @brief Implementation of logging utilities
 */

#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace mathlib {

void Logger::init(spdlog::level::level_enum level) {
    // Create console logger with colors
    auto console = spdlog::stdout_color_mt("mathlib");
    spdlog::set_default_logger(console);

    // Set log level
    spdlog::set_level(level);

    // Set pattern: [timestamp] [level] message
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

    spdlog::info("MathLib logger initialized");
}

}  // namespace mathlib