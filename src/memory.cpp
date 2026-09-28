#include "tinyinfer/memory.hpp"

#include <stdexcept>

namespace tinyinfer
{
    long long num_elements(long long rows, long long columns)
    {
        if (rows <= 0)
        {
            throw std::runtime_error("tensor rows must be positive");
        }

        if (columns <= 0)
        {
            throw std::runtime_error("tensor columns must be positive");
        }

        return rows * columns;
    }

    long long bytes_fp32(long long elements)
    {
        return elements * 4;
    }

    long long bytes_int8(long long elements)
    {
        return elements;
    }

    double bytes_to_mb(long long bytes)
    {
        return bytes / 1'000'000.0;
    }
}