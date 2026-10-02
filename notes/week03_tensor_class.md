# Day 15 - Classes and Tensor Skeleton

## Self notes

- structs are public members hence there is no private members. 
- Think of it like structs are public gyms while classes are private gyms with a few public accessible equipments. 
- Members of a class are private by default.

## What is a class in C++?

class is a user defiend container/template for creating objects

## What is the difference between public and private members?

public members can be accessed from any place but private can be accessed by that class only

## What is a constructor, and when is it called?

A constrcutor is a special member function that is automatically called when an obejct of a class is created

## What is a getter, and why are rows() and cols() getters?

A getter is a public member function that returns information from a private member without exposing the private member directly.

## What does encapsulation mean, and why do we keep rows_, cols_, and data_ private?

Encapsualtion is the practise of building data and methods that operate on that data into a single unit while restricting direct access to some of the object's components

## Why should the Tensor constructor validate dimensions before creating its internal data storage?

The constructor should validate rows and columns before allocating tensor storage so an invalid Tensor cannot be created and a negative size is not passed to std::vector.





# Day 16 - Tensor Indexing and Row-Major Storage

## Self notes

- A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on both const and non-const objects.
- In principle, yes, we could store something like a matrix as a true 2D array. But here's why we flatten it on purpose. Ultimately, even a 2D array ends up flat in memory. So C++ just hides the math from you when you write an array matrix. And the reason we don't use a fixed 2D array is that our tensor sizes are not usually known at compile time. They're decided when the program runs. So std::vector lets us allocate that memory dynamically and safely. Another option is vector<vector<float>>. But that creates lots of little separate allocations under the hood. So memory is scattered and that's not what we want for performance. What we really want is a single contiguous chunk of memory because later, when we do matrix math over and over, contiguous memory is much faster for the CPU cache. So you can think of it like we're building the 2D idea ourselves on top of a flat storage. That index formula: `index=rows*cols+cols` is really just making explicit what C++ normally hides.

## What is row-major storage?

Row-major storage means all elements of a row are stored contiguously before the elements of the next row.

## Why do we store a 2D Tensor inside a 1D std::vector<float>?

We use a 1D std::vector<float> so the Tensor elements are stored in one contiguous block of memory. We then use row-major indexing to treat that 1D storage like a 2D Tensor.

## How does the formula row * cols_ + col convert a 2D position into a 1D index?

specific row x number of column + spcific coulmn gets the index of the position in 1D from a 2D position coordiante

## Why does the non-const at(row, col) return float&?

We do not want to change the copy of the tensor but the value at the original tensor.

## Why do we also need a const version of at(row, col)?

used for read only version were a const variavle can also access the function. we shouldnt be able to accidently change the value using a const version

## Why can print() use rows_, cols_, and at() directly without receiving them as arguments?

print() is a member function of Tensor, so it can directly access that Tensor object's private members such as rows_, cols_, and data_, as well as other member functions like at()





# Day 17 - 