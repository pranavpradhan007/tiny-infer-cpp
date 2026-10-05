#pragma once
#include "tinyinfer/tensor.hpp"
#include <string>
namespace tinyinfer
{
    void save_tensor_text(const Tensor& tensor, const std::string& path);
    tinyinfer::Tensor load_tensor_text(const std::string& path);
}