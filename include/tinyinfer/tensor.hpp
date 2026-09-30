#pragma once

#include <vector>

namespace tinyinfer
{
    class Tensor
    {
        private:
            long long rows_{};
            long long cols_{};
            std::vector<float> data_{};
        public:
            Tensor(long long rows, long long cols);
            long long rows() const {return rows_;} //getter for rows_. we get the data from rows to rows_. They let outside code read private members without directly touching them.
            long long cols() const {return cols_;} //getter for cols_. we get the data from cols to cols_. They let outside code read private members without directly touching them. 

            long long size() const;
    };
}