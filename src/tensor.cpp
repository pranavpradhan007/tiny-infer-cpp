#include "tinyinfer/tensor.hpp"
#include <stdexcept>

namespace tinyinfer
{
    tinyinfer::Tensor::Tensor(long long rows, long long cols)
        :rows_(rows),//we usually initialize members directly
        cols_(cols)
    {
        if (rows <= 0)
        {
            throw std::runtime_error("Tensor rows must be positive");
        }

        if (cols <= 0)
        {
            throw std::runtime_error("Tensor columns must be positive");
        }

        data_.resize(rows * cols); // after validation we are declaring the resize so that -ve number validation can happen after
    }

    long long tinyinfer::Tensor::size() const
    {
        return rows_*cols_;
    };
}