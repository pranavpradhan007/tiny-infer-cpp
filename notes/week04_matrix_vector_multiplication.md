# Day 22 - Naive Matrix-Vector Multiplication

## What is matrix-vector multiplication, and how is each output element calculated?

Matrix-vector multiplication is an operation that takes a matrix and a vector, multiplies them together, and produces a new vector as output. output[i] = sum_j(matrix[i][j] * vector[j])

## Why must the number of matrix columns equal the size of the input vector?

The number of matrix columns must equal the size of the input vector so that every component in the vector has a corresponding coefficient in each row of the matrix during a dot product calculation.

## Why does a matrix with R rows produce an output vector with R elements?

R x C * C = R

## Why does matvec_naive() take const Tensor& and const std::vector<float>& instead of passing them by value?

as we are only reading the vector and tensor not modifying it.

## What is size_t, and why might we use static_cast<long long>(vector.size()) when comparing it with matrix.cols()?

size_t is a cpp variable used for size() values. we use static_cast<long long> as we want to change the size_t to long long before comparing





# Day 23 - MatVec Validation

## What is the purpose of using assert() in our MatVec tests?

assert() checks that a condition we expect to be true is actually true. If it is false, the test fails and helps reveal a bug in our program logic.

## Why do we test cases like 1x1, zero matrix, and identity matrix instead of only the normal 2x3 example?

We test different cases to make sure MatVec works beyond one normal example. 1x1 tests the smallest valid case, the zero matrix checks zero accumulation, and the identity matrix checks that the vector remains unchanged.

## Why is the dimension mismatch test different from the other tests?

The other tests expect a numerical output, while the dimension mismatch test expects matvec_naive() to fail by throwing an exception.





# Day 24 - Dot Product Helper and Function Decomposition

## What does dot_product_row() calculate?

calculates the dot product of the row

## Why did we move the inner MatVec loop into a separate helper function instead of keeping everything inside matvec_naive()?

we can modularize and use helper functions in the future





# Day 25 - Floating-Point Comparison

## Why should we avoid using == when comparing floating-point results from calculations?

as floating point numbers have almost values. like for example 0.1+0.2=0.3 is mathematically true but for comparison of floating point the result would be 0.3000000001 or 2.9999999998

## What is epsilon (eps), and how does almost_equal() use it to compare two numbers?

epsilon is a value for which when we compare we get almost equal result 

## Why do we use std::abs(a - b) instead of simply a - b?

we do not care wether the value is +ve or -ve

## Why is almost_equal() important for our Tiny Infer project, especially when we later implement optimized MatVec operations?

so that the comparison of floating point numbers would not result in random expression values. the values might be mathematically equivalent but differ slightly because of floating point rounding





# Day 26 - Command-Line Interface (CLI)

## What are argc and argv in C++? How do they help our Tiny Infer program receive commands from the terminal?

they are argument count and argument vector. they help in using cli commands 

## Why do we use std::stoll() when reading rows and columns from argv? What is the purpose of pos in our implementation?

std::stoll means string to long long. We use std::stoll() to convert command-line arguments from strings into long long integers. We use pos to check how many characters were processed during conversion. If pos is not equal to the string's size, the input contains extra invalid characters, so we reject it.

## Why do we validate command-line arguments in main() even though our Tensor class and MatVec functions already perform validation?

think of validation as a layered. we need to  validate before in main as to have validation for the cli

## What is the difference between i++ and ++i? Why did we use argv[++i] when reading values after --rows and --cols?

i++ is post-increment. It uses the current value of i first and then increments it by 1.
++i is pre-increment. It increments i by 1 first and then uses the updated value.
We use argv[++i] because we need to access the argument immediately after --rows or --cols, which contains the numerical value.





# Day 27 - MatVec and LLM Inference

## Why is matrix-vector multiplication important in LLM inference?

Matrix-vector multiplication is a fundamental operation in neural networks and LLM inference. An LLM contains weight matrices that transform input vectors into output vectors using operations such as y = Wx + b. During token-by-token decoding, especially with batch size 1, many linear layers perform matrix-vector-like operations. Our matvec_naive() function implements the basic multiplication Wx, helping us understand how numerical computations happen inside an inference engine.

## What is the difference between matrix-vector multiplication (MatVec) and matrix-matrix multiplication (MatMul)?

MatVec multiplies a matrix of size M × K by a vector of size K and produces an output vector of size M. MatMul multiplies two matrices of sizes M × K and K × N, producing an output matrix of size M × N. In LLM inference, MatMul is commonly used during prefill because multiple prompt tokens can be processed together. MatVec is common during single-request, batch-size-1 decoding because the model processes one new token's representation at a time. However, batched decoding can also use MatMul.

## Why are weight matrices in large language models so large?

Weight matrices contain the learned parameters that an LLM uses to transform and process information. These matrices are large because LLMs work with representations containing thousands of features and have many layers with multiple weight matrices in each layer. Larger matrices require more memory to store their parameters and more memory bandwidth to access them during inference. This makes techniques such as quantization and efficient memory access important for optimizing LLM performance.

## Why does C++ performance matter for AI inference?

C++ provides low-level control over memory management, data structures, and CPU execution, which is useful for performance-critical AI operations. We can apply techniques such as SIMD, multithreading, cache-friendly memory access, and quantization to improve numerical computation. Optimized implementations can reduce inference latency, improve throughput, and lower computational costs. Our Tiny Infer project helps us understand these operations manually before learning more advanced CPU and GPU optimizations.





# Day 28 - Week 4 Review

## What did we implement during Week 4?

We implemented naive matrix-vector multiplication using matvec_naive() and refactored its calculation into a dot_product_row() helper. We also added correctness tests using assertions and almost_equal() for floating-point comparisons. Finally, we created a CLI that allows users to specify matrix dimensions through terminal arguments.

## How does matvec_naive() work? 

matvec_naive() multiplies an R × C matrix by a vector of length C and returns a vector of length R. It loops through every matrix row and calls dot_product_row(), which multiplies and sums the corresponding elements. Its time complexity is O(R × C) because every matrix element is processed once.

## How did we test the correctness of our MatVec implementation?

We used assert() to check whether our output matched the expected results. We tested normal multiplication, a 1×1 matrix, a zero matrix, an identity matrix, and mismatched dimensions. We also introduced almost_equal() to account for small floating-point rounding differences.

## How does our CLI make Tiny Infer more useful?

The CLI allows users to specify matrix dimensions directly from the terminal instead of changing the source code or using interactive cin input. This makes it easier to run different workloads repeatedly, automate experiments, and eventually benchmark Tiny Infer's performance.

## What is the most important thing you learned in Week 4, and what are you still confused about?

I learned that matvec_naive is a GEMV multiplication. confusing thing was the argv and argc things we did. other than that it was helpful. the cli stuff with stoll and stoi was also a little confusing as well.