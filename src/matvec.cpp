#include "tinyinfer/matvec.hpp"
#include "tinyinfer/tensor.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>

namespace tinyinfer
{
    std::vector<float> tinyinfer::matvec_naive(const tinyinfer::Tensor& matrix,const std::vector<float>& vector)
    {
        if(matrix.cols()!=static_cast<long long>(vector.size())) //vector.size() returns size_t, and tensor uses long long
        {
            throw std::runtime_error("The matrix columns and size of vector should be the same for multiplication");
        }
        std::vector<float> result(matrix.rows());
        
        for(long long row=0; row<matrix.rows(); row++)
        {
            result[row]=tinyinfer::dot_product_row(matrix, row, vector);
        }
        return result;
    }

    float tinyinfer::dot_product_row(const tinyinfer::Tensor& matrix, long long row, const std::vector<float>& vector)
    {
        float sum{0};
        for(long long col=0; col<matrix.cols(); col++)
            {
                sum+=matrix.at(row,col)*vector[col];
            }
        return sum;
    }

    bool tinyinfer::almost_equal(double a, double b, double eps)
    {
        double abs_diff{std::abs(a-b)};
        if(abs_diff<=eps)
        {
            return true;
        }
        return false;
    }
}