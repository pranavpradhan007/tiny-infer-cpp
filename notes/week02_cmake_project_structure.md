# Day 08 - CMake Basics

## my notes

cmake -S <dir>
Specifies the project root directory, where CMake will find the project to be built. This contains the root CMakeLists.txt file which will be discussed in Step 1 of the tutorial.

When unspecified, defaults to the current working directory.

cmake -B <dir>
Specifies the build directory, where CMake will output the files for the generated build system, as well as artifacts of the build itself when the build system is run.

When unspecified, defaults to the current working directory.

cmake --build <dir>
Runs the build system in the specified build directory. This is a generic command for all generators. For multi-configuration generators, the desired configuration can be requested via:

cmake --build <dir> --config <cfg>

## What is CMake, and is it a compiler?

CMake is a build system generator and it is not a compiler. It uses existing compiler.

## What is CMakeLists.txt?

It is the primary config file. CMake uses this config file and generates standard build files for specific platform like VSCode

## What does add_executable() do?

It builds the executable and uses complier to compile the code as well 

## What does CMAKE_CXX_STANDARD control?

C++ version of the project

## What is the difference between cmake -S . -B build and cmake --build build?

the first command is used to use the root directory as the existing directory and create and use the build directory /build. the second command is used to build the code using the /build directory files.

## Why do we keep generated build files inside the build/ directory?

we keep the build files inside the build/ directory so that the cmake can build the executables and link headers away from source code. basically a sandbox where everything is stored and build correctly and is gitignored





# Day 09 - 