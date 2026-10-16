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





# Day 30 - CTest Integration

## What is CTest, and why are we using it in Tiny Infer?

CTest gives us one standard command to run tests. we can use this same command in GitHub Actions so that code changes are automatically tested before merging

## What is the difference between Catch2 and CTest?

Catch2 verifies whether Tensor and MatVec behave correctly. CTest gives us one standard command to run those tests.

## What is the purpose of enable_testing() and add_test() in CMake?

CMake only generates tests if the enable_testing() command has been invoked. add_test() adds a test called name ane command

## What happens when we execute the following command: ctest --test-dir build -C Debug --output-on-failure?

runs your project's automated test suite using CMake's test runner (CTest) with specific configuration and logging behaviors

## Why might CTest show 1/1 tests passed even though we wrote five Catch2 test cases?

it does not know there are individual tests instead it only knows it is oinly 1 test





# Day 31 - Basic Timing with std::chrono

## What is std::chrono, and why are we using it in Tiny Infer?

std::chrono is a library which is basically a date and time library. we use it in tinyinfer as we need to compare and benchmark different matmul and matvec operations

## What is the difference between std::chrono::steady_clock::now(), a time point, and a duration?

std::chrono::steady_clock::now() is a function that returns a time point, a time point represents a specific instant in time, and a duration represents an amount of elapsed time between two instants

## Why do we use std::chrono::duration<double, std::milli> and .count()?

std::chrono::duration<double, std::milli> represents an amount of time measured in milliseconds using a double.
Here, double allows fractional values, std::milli specifies milliseconds, and .count() retrieves the numerical value of the duration.
This is important because fast operations may take less than one millisecond, and we want to preserve that precision rather than round the result to a whole number.

## Why do we generate the Tensor and vector before starting the timer?

We generate the Tensor and vector before starting the timer because we want to measure only the execution time of matvec_naive().
If we include input generation, memory allocation outside MatVec, or console printing, those operations will increase the measured time.
By excluding them, we can more accurately measure the operation we're trying to optimize.

## Why do we benchmark in Release mode, and how do you interpret your results?

Release mode generally enables compiler optimizations that improve execution performance, whereas Debug mode primarily supports easier debugging.
Our naive MatVec has time complexity \(O(R \times C)\). When we double both matrix dimensions, the number of elements increases by four times, so the computational work also increases approximately fourfold.
However, actual execution time does not necessarily increase by exactly four times because of CPU caching, memory access patterns, processor frequency, operating-system scheduling, and measurement overhead. Repeated benchmarks are necessary for reliable performance comparisons.





# Day 32 - 