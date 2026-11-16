#pragma once

#include <cstdint>
#include <vector>

namespace tinyinfer
{
    class QuantizedTensor
    {
        private:
        int rows_;
        int cols_;
        float scale_;
        std::vector<std::int8_t> data_;

        public:
        QuantizedTensor(int rows, int cols, float scale);
        int rows() const {return rows_;}
        int cols() const {return cols_;}
        float scale() const {return scale_;}

    };
}