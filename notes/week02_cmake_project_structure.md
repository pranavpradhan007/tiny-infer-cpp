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





# Day 09 - Header and Source Separation

## What is the difference between a declaration and a definition?

declaration is declaring the function before hand and definition is the writing the function body

## What is the purpose of a .hpp header file?

header files place every function declaration together even the structs as well

## What is the purpose of a .cpp source file?

we can modularize the code into different files so that main wont be bloated and confusing

## Why do we use #pragma once?

pragma once is used as a header guard so that our declarations are guarded from being declared and copied again and again

## Why do we include memory.hpp instead of memory.cpp?

that is a header file not a source code file so that it can be linked correctly to memory.cpp

## What is the difference between compilation and linking?

compilation is compiling the code file individually but linking is linking the exectuables to each other





# Day 10 - Namespaces

## What is a namespace in C++?

namespaces exists in c++ so that there would be explicit naming of certain collision proven naming of things and we can use them more clearly

## Why do namespaces help prevent naming conflicts?

Namespaces help preventing conflicts as different namespaces can have different namespaces

## What does the :: scope resolution operator do?

it defines which namespace the certain function/variable belongs to

## What is the difference between std::cout and tinyinfer::bytes_fp32()?

cout from standard namespace and bytes_fp32 from tinyinfer namespace

## Why should the declaration and definition of a function be inside the same namespace?

so that there wont be mismatch and collisions

## Why can using namespace std; become risky in larger projects?

due to conflicts with differnt functions from the standard namespace when the project evolves





# Day 11 - Error Handling

## What is an exception in C++?

exception is the runtime error

## What does throw do?

throw throws the exception for catch to catch

## What is std::runtime_error used for?

report errors that happen while program runs due to events outside the programs control

## What is the difference between try and catch?

try is a loop which says the program to try and stop for any execptions while catch cathces them

## Why should low-level functions throw errors instead of always printing errors themselves?

they should validate what they are claiming to have as datatype or like a validation check for the function itself

## What does exception.what() return?

message of the exception





# Day 12 - References and Pointers

## What is the difference between pass by value and pass by reference?

pass by value is copying the element again to stack and by reference is refering the original value in the stack

## What is a reference in C++?

reference is the address of the value

## What is a pointer in C++, and what does it store?

pointer is a object which stores address of the value

## What is the difference between &number, ptr, and *ptr?

address of number as a lvalue reference, address stored in pointer, derefering the ptr to show us the underlyiong object

## What is nullptr, and why should we never dereference a null pointer?

nullptr is a special keyword which is basically giving a null value to the pointer. dereferencing does not make sense as there is nothing to dereference

## How are Python variables/references different from C++ variables, references, and pointers?

In Python, variables usually refer to objects automatically and you do not explicitly work with pointers or references. In C++, variables can directly contain values, references can alias existing objects, and pointers explicitly store memory addresses





# Day 13 - RAII and Memory Safety

## Why will I avoid raw new and delete in Tiny Infer?

I will avoid the raw new and delete as there can be mismanagement of memory. I will use the std::vector<float> to auto manage memory for me using RAII principles. Tensor data will use std::vector<float>. I will avoid manual dynamic arrays.

## What is RAII?

Resource Acquisition Is Initialization is a principle that the code that creates a resource also cleans it up automatically.

## What is a memory leak?

memory leak is forgeting to deallocate a memory before we make change to the dynamically allocated pointer.

## Why can raw new and delete be dangerous?

manual memory management, dangling pointers, dereferenceing thealready deleted pointer, etc

## What is a dangling pointer?

 a pointer that points to a memory location that has already been deleted or freed

## Why is std::vector safer than manually allocating a dynamic array?

it auto manages memory allocation and destruction for us

## Why are we choosing std::vector<float> for Tiny Infer tensor storage?

it auto manages memory allocation and destruction for us so we dont have to think about dynamic arrays





# Day 14 - 