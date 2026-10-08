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





# Day 26 - 