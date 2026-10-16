
cmake_minimum_required(VERSION 3.30)
project(tiny-infer-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# 1. Create the reusable Tiny Infer library
add_library(tinyinfer_core
    src/memory.cpp
    src/file_io.cpp
    src/vector_utils.cpp
    src/tensor.cpp
    src/tensor_io.cpp
    src/matvec.cpp
)

# 2. Make headers accessible to the library and its users
target_include_directories(tinyinfer_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# 3. Create the CLI executable
add_executable(tinyinfer
    src/main.cpp
    benchmarks/matvec_bench.cpp
)

# 4. Link the CLI to our reusable library
target_link_libraries(tinyinfer PRIVATE
    tinyinfer_core
)

# 5. Download and configure Catch2
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(Catch2)

# 6. Create a separate executable for unit tests
add_executable(tinyinfer_tests
    tests/test_tensor.cpp
    tests/test_matvec.cpp
)

# 7. Link the tests to Tiny Infer and Catch2
target_link_libraries(tinyinfer_tests PRIVATE
    tinyinfer_core
    Catch2::Catch2WithMain
)

add_test(
    NAME tinyinfer_unit_tests
    COMMAND tinyinfer_tests
)