# Fetch Catch2 from GitHub
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2  # Use a specific version
)

FetchContent_MakeAvailable(Catch2)

# Add Catch2's CMake modules to the path
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Include CTest integration
include(CTest)
include(Catch)

# Create test executable with all test files
add_executable(tests
    test_main.cpp
    test_basic.cpp
    test_mathlib.cpp
)

# Link against our library and Catch2
target_link_libraries(tests PRIVATE 
    mathlib
    Catch2::Catch2
)

# Coverage flags are automatically inherited from mathlib
# because we used PUBLIC in the library's target_compile_options
# No need to add them again here!

# Automatically discover tests
catch_discover_tests(tests)