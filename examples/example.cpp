/**
 * @file example.cpp
 * @brief Example program demonstrating vcpkg dependency usage
 *
 * This example shows how to use:
 * - fmt: Modern formatting library
 * - spdlog: Fast logging library
 * - nlohmann_json: JSON library
 */

#include "logger.h"
#include "mathlib.h"

#include <iostream>
#include <vector>

#include <fmt/color.h>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    // Initialize logger
    mathlib::Logger::init(spdlog::level::debug);

    fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
               "=== MathLib Example with vcpkg Dependencies ===\n\n");

    // Example 1: Basic math operations with logging
    fmt::print(fmt::emphasis::bold, "Example 1: Basic Operations\n");

    double x = 7.5;
    mathlib::Logger::info("Computing square of {}", x);
    double x_squared = mathlib::square(x);
    fmt::print("  square({}) = {}\n", x, x_squared);

    int n = 10;
    mathlib::Logger::info("Computing factorial of {}", n);
    double n_factorial = mathlib::factorial(n);
    fmt::print("  factorial({}) = {}\n\n", n, n_factorial);

    // Example 2: Processing data with JSON
    fmt::print(fmt::emphasis::bold, "Example 2: JSON Configuration\n");

    // Create a JSON configuration
    json config = {
        {"name", "MathLib"},
        {"version", "1.0.0"},
        {"parameters", {{"tolerance", 1e-6}, {"max_iterations", 100}, {"enable_logging", true}}},
        {"test_values", {2.0, 3.5, 5.0, 7.5, 10.0}}};

    mathlib::Logger::debug("Configuration: {}", config.dump(2));

    // Read configuration
    std::string name = config["name"];
    double tolerance = config["parameters"]["tolerance"];
    std::vector<double> test_values = config["test_values"];

    fmt::print("  Configuration loaded:\n");
    fmt::print("    Name: {}\n", name);
    fmt::print("    Tolerance: {}\n", tolerance);
    fmt::print("    Test values: [");
    for (size_t i = 0; i < test_values.size(); ++i) {
        fmt::print("{}{}", test_values[i], (i < test_values.size() - 1) ? ", " : "");
    }
    fmt::print("]\n\n");

    // Example 3: Compute and store results in JSON
    fmt::print(fmt::emphasis::bold, "Example 3: Results Export\n");

    json results = json::array();

    for (double value : test_values) {
        json result_entry = {{"input", value},
                             {"square", mathlib::square(value)},
                             {"factorial", mathlib::factorial(static_cast<int>(value))}};
        results.push_back(result_entry);

        mathlib::Logger::debug("Processed value: {} -> square={}, factorial={}", value,
                               mathlib::square(value), mathlib::factorial(static_cast<int>(value)));
    }

    // Pretty-print results
    fmt::print("  Results (JSON):\n{}\n\n", results.dump(2));

    // Example 4: Formatted output with colors
    fmt::print(fmt::emphasis::bold, "Example 4: Colored Output\n");

    for (const auto& entry : results) {
        double input = entry["input"];
        double square_val = entry["square"];
        double factorial_val = entry["factorial"];

        fmt::print("  ");
        fmt::print(fg(fmt::color::cyan), "Input: {:6.2f}", input);
        fmt::print(" | ");
        fmt::print(fg(fmt::color::yellow), "Square: {:8.2f}", square_val);
        fmt::print(" | ");
        fmt::print(fg(fmt::color::magenta), "Factorial: {:12.2f}", factorial_val);
        fmt::print("\n");
    }

    fmt::print("\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
               "=== All vcpkg dependencies working! ===\n");

    mathlib::Logger::info("Example completed successfully");

    return 0;
}