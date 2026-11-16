#include "tinyinfer/quantized_tensor.hpp"
#include "tinyinfer/tensor.hpp"
#include <stdexcept>
#include <cmath>


namespace tinyinfer
{
    tinyinfer::QuantizedTensor::QuantizedTensor(int rows, int cols, float scale):
    rows_(rows),
    cols_(cols),
    scale_(scale)
    {
        if (rows <= 0)
        {
            throw std::invalid_argument("Tensor rows must be positive");
        }

        if (cols <= 0)
        {
            throw std::invalid_argument("Tensor columns must be positive");
        }
        
        if (scale<=0 || !std::isfinite(scale))
        {
            throw std::invalid_argument("Scale must be positive and finite");
        }

        const std::size_t r = static_cast<std::size_t>(rows);
        const std::size_t c = static_cast<std::size_t>(cols);

        if (r > data_.max_size() / c)
        {
            throw std::length_error("Tensor dimensions are too large");
        }
        
        data_.resize(r * c);
    }

    const std::vector<std::int8_t>& tinyinfer::QuantizedTensor::raw_data() const
    {
        return data_;
    }
    
    std::vector<std::int8_t>& tinyinfer::QuantizedTensor::raw_data() 
    {
        return data_;
    }

}