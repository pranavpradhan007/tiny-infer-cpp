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
            long long rows() const {return rows_;} //getter for rows_.
            long long cols() const {return cols_;} //getter for cols_.


            long long size() const;
            float& at(int row, int col); //modifyable as non constant
            float at(int row, int col) const; //read only as constant
            void print() const;

    };
}