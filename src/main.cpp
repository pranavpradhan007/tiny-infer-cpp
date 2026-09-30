#include "tinyinfer/tensor.hpp"
#include <iostream>
#include <stdexcept>

int main()
{
    long long rows{};   
    long long cols{};

    std::cout<<"Enter the number of rows: ";
    std::cin>>rows;
    std::cout<<"Enter the number of columns: ";
    std::cin>>cols;
    try
    {
        tinyinfer::Tensor matrix{rows, cols};
        std::cout<<"Rows: "<<matrix.rows()<<'\n';
        std::cout<<"Columns: "<<matrix.cols()<<'\n';
        std::cout<<"The total number of elements in the tensor: "<<matrix.size()<<'\n';
        return 0;

    }
    catch(const std::runtime_error& exception)
    {
        std::cerr<<"Error: "<<exception.what()<<'\n';
        return 1;
    }
    
}