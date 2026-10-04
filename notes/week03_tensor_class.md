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





# Day 17 - Bounds Checking and Exceptions

## Self notes

- For a Tensor: rows_ = 2 cols_ = 3 : a row must satisfy: `0 <= row < rows_` And a column must satisfy: `0 <= col < cols_`

## What condition makes a Tensor index (row, col) out of bounds?

For a Tensor: rows_ = 2 cols_ = 3 : a row must satisfy: `0 <= row < rows_` And a column must satisfy: `0 <= col < cols_`

## Why is std::out_of_range a better exception choice for invalid Tensor indices than a generic error?

std::out_of_range is appropriate because the requested row or column is outside the valid range of indices for the Tensor.

## Why must the bounds check happen before accessing data_[index]?

or we can have funny situations with negative indexes and non existant indexes of an array





# Day 18 - Tensor Utility Methods

## Self notes

- for range-based for loops, prefer to define the element type as:
    - auto when you want to modify copies of the elements.
    - auto& when you want to modify the original elements.
    - const auto& otherwise (when you just need to view the original elements).

## What does fill(float value) do to the Tensor?

fills the tensor with the float value

## What does raw_data() return, and how is it different from at(row, col)?

returns the raw data which is the vector/tensor we are storing. at() function gives us the specific row and column to change while raw data gives us the original data

## What is the difference between returning std::vector<float> and returning std::vector<float>&?

copying vs pointing to the original memory space

## Why did we use const std::vector<float>& data{matrix.raw_data()}; when calculating the sum?

we did not want to create the copy of the vector again but want to see what is the sum afterwards even if we change a specific element in the matrix after data copy is established.





# Day 19 - Random Tensor Generation

## What is a seed in random number generation, and why does the same seed produce the same sequence?

A seed is the initial starting value used to initialize a pseudo-random number generator. Since the generator follows a deterministic algorithm, the same seed produces the same sequence.

## What is the role of std::mt19937?

Mersenne Twister 64 bit unsigned integer which is a pseudo random value.

## What does std::uniform_real_distribution<float>(min, max) do?

creates a uniform distribution in interval [min,max)

## What is the difference between random_vector() and random_tensor()?

random_vector() produces a new random vector while random_tensor() produces a new random tensor

## Why does random_tensor() use raw_data() instead of repeatedly calling at(row, col) for every element?

raw_data() gives us the underlying data_ in the tensor while at() is used for a specific position in the tensor





# Day 20 - 