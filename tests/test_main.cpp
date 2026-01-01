// This file provides the main() function for Catch2 v3.x
// It only needs to be compiled once and shared across all test files

#include <catch2/catch_session.hpp>

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}