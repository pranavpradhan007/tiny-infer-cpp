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





# Day 23 - 