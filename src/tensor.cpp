#include "tinyinfer/tensor.hpp"
#include <stdexcept>
#include <iostream>
#include <random>

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
    }

    float& tinyinfer::Tensor::at(int row, int col)
    {
        long long index{};
        if(row<0||row>=rows_||col<0||col>=cols_)
        {
            throw std::out_of_range("tensor index out of bounds");
        }
        index = row *cols_ +col; //the indexing formula for the vector storage.specific row x number of columns + the specific column
        return data_[index];
    }

    float tinyinfer::Tensor::at(int row, int col) const
    {
        long long index{};
        if(row<0||row>=rows_||col<0||col>=cols_)
        {
            throw std::out_of_range("tensor index out of bounds");
        }
        index = row *cols_ +col;
        return data_[index];
    }

    void tinyinfer::Tensor::print() const
    {
        for(int i{0}; i<rows_; i++)
        {
            for(int j{0}; j<cols_; j++)
            {
                std::cout<<at(i ,j)<<" ";
            }
            std::cout<<'\n';
        }
    }

    void tinyinfer::Tensor::fill(float value)
    {
        for(auto& element : data_)
        {
            element=value;
        }
    }

    std::vector<float>& tinyinfer::Tensor::raw_data()
    {
        return data_;
    }

    const std::vector<float>& tinyinfer::Tensor::raw_data() const
    {
        return data_;
    }

    std::vector<float> tinyinfer::random_vector(int size, float min, float max)
    {
        std::random_device rd;//seed part for like seed 42 we can do something like int seed{42}; std::mt19937 gen(seed);
        std::mt19937 gen(rd());//generate part 
        std::uniform_real_distribution<float> dis(min,max); //distribution part
        std::vector<float> vector(size); // () is the  constructor and {} is the value initialization

        for(int i{0}; i<size; i++)
        {
            vector[i]=dis(gen); //distribution of the generated random variable
        }
        return vector;
    }

    tinyinfer::Tensor tinyinfer::random_tensor(long long rows, long long cols, float min, float max)
    {
       
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min,max);
        tinyinfer::Tensor rtensor{rows , cols};
        std::vector<float>& data{rtensor.raw_data()};
        for(auto& element:data)
        {
            element=dis(gen);
        }
        return rtensor;

    }
}