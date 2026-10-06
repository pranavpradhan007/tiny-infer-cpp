#include "tinyinfer/matvec.hpp"
#include "tinyinfer/tensor.hpp"
#include <vector>
#include <stdexcept>

namespace tinyinfer
{
    std::vector<float> tinyinfer::matvec_naive(const tinyinfer::Tensor& matrix,const std::vector<float>& vector)
    {
        if(matrix.cols()!=static_cast<long long>(vector.size())) //vector.size() returns size_t, and tensor uses long long
        {
            throw std::runtime_error("The matrix columns and size of vector should be the same for multiplication");
        }
        std::vector<float> result(matrix.rows());
        float sum{0};
        for(int row=0; row<matrix.rows(); row++)
        {
            sum=0;
            for(int col=0; col<matrix.cols(); col++)
            {
                sum+=matrix.at(row,col)*vector[col];
            }
            result[row]=sum;
        }
        return result;
    }
}