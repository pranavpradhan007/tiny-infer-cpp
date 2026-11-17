#include "tinyinfer/quantization_metrics.hpp"
#include "tinyinfer/tensor.hpp"
#include "tinyinfer/quantized_tensor.hpp"
#include <stdexcept>
#include <cstdint>
#include <cstddef>
#include <cmath>

namespace tinyinfer
{
    float mean_absolute_error(const tinyinfer::Tensor& a, const tinyinfer::Tensor& b)
    {
    
        if(a.rows()!=b.rows() || a.cols()!=b.cols())
        {
            throw std::invalid_argument("Rows and cols of the tensors do not match");
        }
        for (float value : a.raw_data())
        {
            if(!std::isfinite(value))
            {
                throw std::invalid_argument("Tensor contains non finite values");
            }
        }
        for (float value : b.raw_data())
        {
            if(!std::isfinite(value))
            {
                throw std::invalid_argument("Tensor contains non finite values");
            }
        }
        double sum{0.0};
        float abs_diff{0};
        for(std::size_t i{0};i<a.raw_data().size(); i++ )
        {
            abs_diff=std::abs(a.raw_data()[i]-b.raw_data()[i]);
            sum+=abs_diff;
        }
        float mae = static_cast<float>(sum / a.raw_data().size());
        return mae;
    }

    float max_absolute_error(const tinyinfer::Tensor& a, const tinyinfer::Tensor& b)
    {
        if(a.rows()!=b.rows() || a.cols()!=b.cols())
        {
            throw std::invalid_argument("Rows and cols of the tensors do not match");
        }
        for (float value : a.raw_data())
        {
            if(!std::isfinite(value))
            {
                throw std::invalid_argument("Tensor contains non finite values");
            }
        }
        for (float value : b.raw_data())
        {
            if(!std::isfinite(value))
            {
                throw std::invalid_argument("Tensor contains non finite values");
            }
        }
        float max{0};
        float abs_diff{0};
        for(std::size_t i{0};i<a.raw_data().size(); i++ )
        {
            abs_diff=std::abs(a.raw_data()[i]-b.raw_data()[i]);
            if(abs_diff>max)
            {
                max=abs_diff;
            }
        }
        return max;
    }

    double compression_ratio_fp32_to_int8(const tinyinfer::Tensor& a)
    {
        std::size_t N{a.raw_data().size()};
        double fp32_storage(N*sizeof(float));
        double int8_storage(N*sizeof(std::int8_t));
        return (fp32_storage/int8_storage);
    }

}