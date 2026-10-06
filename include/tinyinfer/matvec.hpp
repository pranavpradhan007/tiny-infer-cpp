#pragma once
#include "tinyinfer/tensor.hpp"
#include <vector>

namespace tinyinfer
{
    std::vector<float> matvec_naive(const tinyinfer::Tensor& matrix, const std::vector<float>& vector);
    float dot_product_row(const tinyinfer::Tensor& matrix, long long row, const std::vector<float>& vector);

}