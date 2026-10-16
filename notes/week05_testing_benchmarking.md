# Day 29 -  Catch2 Unit Testing

## What is unit testing, and why are we using Catch2 in Tiny Infer?

Unit testing is the process of checking individual functions or components to verify that they produce the expected results. We use Catch2 to automatically test our Tensor and MatVec implementations, including normal outputs, indexing, and exceptions. This will help us ensure that future optimizations do not break existing functionality.

## What is the difference between TEST_CASE(), REQUIRE(), and REQUIRE_THROWS_AS()?

TEST_CASE() standalone test usint, REQUIRE() asserts that a boolean expression evaluets to true, REQUIRE_THROWS_AS() verifies if code throws any specific c++ errors

## Why did we create tinyinfer_core using add_library() instead of keeping all our source files inside add_executable()?

We created tinyinfer_core to separate reusable numerical implementations from executable-specific code. Both our CLI (tinyinfer.exe) and test executable (tinyinfer_tests.exe) need access to the same Tensor and MatVec functions. Using a library lets both executables link to the same implementation without duplicating the source code in each executable target.

## What is the purpose of FetchContent and Catch2::Catch2WithMain in CMake?

FetchContent is a CMake module used to obtain external dependencies such as Catch2 and make them available during configuration.
Catch2::Catch2WithMain is a Catch2 library target that provides both the testing framework and a main() function for running tests.
We use it because our test files contain TEST_CASE() definitions but do not have their own main() function.

## What is the difference between Debug and Release builds?

Debug builds are primarily used during development and debugging. They usually disable compiler optimizations and include debugging information, making it easier to investigate errors.
Release builds generally enable compiler optimizations to improve execution performance. We use Release builds for benchmarking because we want to measure the performance of optimized machine code.





# Day 30 - 