#include "tinyinfer/quantization.hpp"
#include "tinyinfer/tensor.hpp"
#include <stdexcept>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

namespace tinyinfer
{
    tinyinfer::QuantizedTensor quantize_int8(const tinyinfer::Tensor& tensor)
    {

        if (tensor.rows() > std::numeric_limits<int>::max() || tensor.cols() > std::numeric_limits<int>::max())
        {
            throw std::invalid_argument("Tensor dimensions exceed supported INT8 tensor size");
        }

        for (float value : tensor.raw_data())
        {
            if(!std::isfinite(value))
            {
                throw std::invalid_argument("Tensor contains non finite values");
            }
        }

        float max_abs{std::abs(*std::max_element(tensor.raw_data().begin(), tensor.raw_data().end(), [](float a, float b){
            return std::abs(a)<std::abs(b);
        }))}; // basiclly abs(max(begining, ending, comparison operator here it is a lambda function))
    
        float s{(max_abs==0.0f) ? 1.0f : max_abs/127.0f};

        if(s==0.0f)
        {
            s=std::numeric_limits<float>::min();
        }

        tinyinfer::QuantizedTensor qtensor(static_cast<int>(tensor.rows()), static_cast<int>(tensor.cols()), s);

        std::size_t i =0;

        int q{0};
        

        for(const auto& data : tensor.raw_data())
        {
            float rounded{std::round(data/s)};
            float clamped{std::clamp(rounded,-127.0f,127.0f)};
            q = static_cast<int>(clamped);
            qtensor.raw_data()[i] = static_cast<std::int8_t>(q); //get the position and insert the value in that position of qtensor
            ++i;
        }

        return qtensor;
    }


    
}