#pragma once

#include "tinyinfer/quantization.hpp"
#include "tinyinfer/tensor.hpp"
#include "tinyinfer/quantized_tensor.hpp"

namespace tinyinfer
{
    float mean_absolute_error(const tinyinfer::Tensor& a, const tinyinfer::Tensor& b);
    float max_absolute_error(const tinyinfer::Tensor& a, const tinyinfer::Tensor& b);
    double compression_ratio_fp32_to_int8(const tinyinfer::Tensor& a);
}