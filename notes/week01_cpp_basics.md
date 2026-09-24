# Day 01 - C++ Basics and First Compile

## What is C++?

C++ is a programming language used for high performance computing.

## What is source code?

Source code is the code base of the program. The source code doesn't necessarily mean the whole program but the exectuibles and the source code and libraries together means a program.

## What is a compiler?

Compiler is the main engine of C++ code. It acrs as a translator between human and machine.

## What is an executable?

Executable is the executable file we develop after complting the source code.

## What is main()?

main() function is the function which is the one that gets sequentially executed line by line for a C++ program. This is the function where the main source code lives apart from library source codes.

## What happens after I change main.cpp?

After i change main.cpp if i dont compile, the exectuable remains the same and then the same program is then run again. If i change syntax, we get a syntax error.

## Why do I need to compile again?

To change the exectuable.

## How is running C++ different from running Python?

In python the interpretor sequentially runs the code line by line at runtime but in c++ we need to compile the source code everytime we make any changes.

## What compiler error did I encounter today?

I encountered an error related to std::cout. I need to understand what std:: means and why cout belongs to it.

## What confused me today?

Why do we need the use of std:: before cout




# Day 02 - Variables, Types, and Input/Output

## Self Notes

1. [[maybe_unused]] is used when the variable might not be used further down: 

    [[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused
    [[maybe_unused]] double gravity { 9.8 }; // Don't complain if gravity is unused
    [[maybe_unused]] double phi { 1.61803 }; // Don't complain if phi is unused
2. Using int x{} , int x() is preferred. mostly using int x{} as if intitalized int x{4.5} , complier will throw an error. Maybe it would be an issue with vectors later on?


## What is a variable?

The variable is the named object/storage that contains the value.

## What is a data type?

data type is a fixed types of data c++ can handle.

## What is the difference between int, float and double?

int is integer, float has fractional and double is double precision of float

## What does bool represent?

bool means boolean values like true or false

## What does char represent?

char is a single unit of charectar in c++

## What is std::string?

string is sequence of many charectars

## What does std::cout do?

it prints out in the console

## What does std::cin do?

it takes user inputs

## What is initialization?

Giving a variable its initial value when the variable is created.

## What is assignment?

assignement is the way a variable can be assigned a value

## Why can an uninitialized variable be dangerous?

it can print out garbage value

## What does << mean when used with std::cout?

insertion operator

## What does >> mean when used with std::cin?

extraction operator

## Why does FP32 require more memory than INT8?

as fp32 is 4 times the int memory.
![1787865581448](image/week01_cpp_basics/1787865581448.png)
![1787865601518](image/week01_cpp_basics/1787865601518.png)

## What confused me today?

not much, just why fp32 requires more memory than int and how does it look in binary.





# Day 03 - Functions and Clean Code

## What is a function?

function is a way to use the code again and again

## Why are functions useful?

modulartity, readbility and resuablitiy

## What is a parameter?

parameter is a variable decalerd in function definition int func(int parameter,int parameter)

## What is an argument?

argument is the real value for the function func(0,9)

## What is the difference between parameter and argument?

one is initalization and one is setting of value

## What is a return value?

return value is the value used for returning and setting the variable to the memory

## What does void mean for a function?

reutrn nothing

## What is local scope?

which is initatied in local functions, other functions cannot use it until it is declared for use and referenced properly

## What is pass by value?

using value directly

## What is pass by reference?

using address/ pointers to access memory slots 

## What happens if a function modifies a value passed by value?

nothing changes as it is a copy

## What can happen if a function modifies a non-const reference?

value is changed as og is changed as pointed to address

## What does const mean?

constant variable which should not be modified 

## Why might copying a huge Tensor be more expensive than copying an integer?

tensor are huge and intger are smaller

## What confused me today?

const declaration inside a function parameter. also the parameter initialization.





# Day 04 - Loops and Vectors

## What is a loop?

loop is a way to automate the repeatble cin and cout stuff

## What is the difference between a for loop and a while loop?

while loop is used when bounds are not really clear but for is used when bounds are clear

## What is std::vector?

vector is a container. it is basically an array.

## What do .size() and push_back() do?

size() is a method for vector which calculates the size that is the length of the array. push_back() is the method in array which helps in using push function in stack to push on top of the stack. to pop is pop_back(). we can even use emplace_back() method which is similar to push_back() method

## Why does vector indexing start at 0, and what happens if you access an invalid index?

vector index starts at 0 as you can imagine that we are calcualting the distance from first elkement. you can get error when accessing invalid index

## Why do we pass a vector using const & instead of by value?

using const vector<type>& name helps in accessing by address and not by value. this helps in function not calling the whole vector value whenever it wants to. using address points to address of the vector

## What is the time complexity of sum_vector() and max_abs()?

O(n) spcae for sum is O(n) but for max is O(1)

## Why will max_abs() matter later for INT8 quantization?

as we are going to divide it up by the size of int8 which is max_abs/127

## What confused me today?

I think today was first time i used stackoverflow and internet to help me with the problem. the main thing was calculation of max value but i got it. other was const & when using vector.





# Day 05 - Structs and Data Modeling

## What is a struct?

structs are containers in c++.

## What is a data member?

anything in the structs are called data member

## Why did we group rows and cols into TensorShape instead of keeping them separate?

i can now use many times without worrying about the rows and cols differently. 

## How do you access members of a struct?

using . operator

## What is the difference between a struct type and an object created from that struct?

struct is a strcuture or a blueprint while object is the one tat uses the blueprint. think of it like a house and its blueprint. there can be many houses of the same blueprint.

## What confused me today?

relatively simple. what confused me was that int to string conversion. to_string is used for int type conversion. at first i misread the problem and was inputting the elements as well for the tensor but then i abandoned it after reading the problem thoroughly.





# Day 06 - File I/O

## What is file I/O?

we can input output files using buffer stream

## What is the difference between ifstream and ofstream?

ifstream is reading the file and ofstream writing to a file

## Why should we check whether a file opened successfully?

if the file does not exist then we should get an error

## How does while (inf >> value) work when reading a file?

it checks the file until it is empty and writes to a value variable which can be used to display the file

## What is the difference between data in RAM and data stored in a file?

RAM is volatile and hence can be deswtroyed when program ends. Storing in file is storing the data until we change the data in the file or delete it. it stays the same

## Why will file I/O matter later when we work with GGUF/model files?

We will save the model GGUF files and laod them from the disk rather than memory





# Day 07 - Week 1 Review

## What happens between a .cpp file and an executable?

.cpp file is where we write the code. executable is where the machine translated code lives

## What are the main primitive/fundamental types we used this week?

we used int, long long, float, double, char, bool.

## What is std::vector, and why did we use it instead of a raw array?

vector is a better way to use an array than raw array. raw arrays have a few disadvantages which in turn would make our code unprotected. vector has built in methods such as push_back(), pop_back() and emplace_back() which can be accessed with . operator and is helpful in stacking the data.

## What does const mean?

const means constant that is that value cannot change directly from anywhere else in the code apart from where it is declared.

## What is the difference between pass-by-value and pass-by-reference?

pass by value copies the data/value/heap to the function call again which in turn loses memory. pass by reference uses address of the memory to get the actual data stored in that specific address of the memory and does not make any copies as well when a function is called.

## What is a struct, and why did we create TensorShape?

struct is a structure/container which can be used to hold data. it can be used as a user defined data type. we used it for TensoShape as we do not need to define rows and colums again and again.

## What confused me most during Week 1, and do I understand it now?

Pretty much easy this week. Got to refresh my memory for basic concepts in LLM inference and C++ as well. Not much confusing apart from a few things I have yet to encounter. The confusion for daily progress has been reviewed and now I have a better understanding of the underlying basic concepts.