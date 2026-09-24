# Tiny Infer : From-Scratch C++ Inference Engine

A from-scratch C++ project for learning low-level AI inference systems, memory handling, tensor operations, quantization, model formats, benchmarking, and performance optimization.

## Project Goal

The goal of this project is to learn modern C++ by building a small inference-oriented systems project from the ground up.

Instead of only doing isolated beginner exercises, each topic is connected to concepts used in AI inference systems.

Over time, this project will include:

- C++ fundamentals
- CMake
- Tensor representation
- Matrix-vector multiplication
- Benchmarking
- INT8 quantization
- GGUF parsing
- Unit testing
- Performance optimization
- Optional Python bindings

## Learning Approach

This project is being built incrementally.

Each study day includes:

- learning a new C++ concept
- implementing a small related exercise
- documenting what was learned
- testing the implementation
- committing progress to GitHub

The goal is to understand the implementation rather than only complete the final project.

## Week 1 Progress

### Day 01 - Setup and First Compile
- Learned how C++ source code is compiled
- Understood source code, compiler, executable, and `main()`
- Wrote and compiled the first C++ program manually

### Day 02 - Variables, Types, and Input/Output
- Learned fundamental data types
- Practiced `std::cin` and `std::cout`
- Built a tensor memory estimator for FP32 and INT8

### Day 03 - Functions and Clean Code
- Learned functions, parameters, arguments, and return values
- Practiced pass-by-value and pass-by-reference
- Refactored the tensor memory estimator into separate functions

### Day 04 - Loops and Vectors
- Learned `for` and `while` loops
- Learned `std::vector`
- Implemented vector creation, summation, and maximum absolute value calculations

### Day 05 - Structs and Data Modeling
- Learned how structs group related data
- Created a `TensorShape` struct
- Added shape validation and element-count calculations

### Day 06 - File I/O
- Learned `ifstream` and `ofstream`
- Saved vector data to a text file
- Loaded vector data back from disk

### Day 07 - Week 1 Review
- Reviewed C++ fundamentals from Week 1
- Documented lessons learned
- Prepared the project for Week 2

## Current Status

- Week 1 completed.

## Week 2 will focus on:

- CMake
- project structure
- header and source separation
- namespaces
- error handling
- references and pointers
- RAII and memory safety