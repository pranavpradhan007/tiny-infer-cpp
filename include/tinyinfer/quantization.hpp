#pragma once

#include "tinyinfer/quantized_tensor.hpp"
#include "tinyinfer/tensor.hpp"
#include <vector>

namespace tinyinfer
{
    tinyinfer::QuantizedTensor quantize_int8(const tinyinfer::Tensor& tensor);
    
}