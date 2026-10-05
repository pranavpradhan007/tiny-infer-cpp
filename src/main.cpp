#include "tinyinfer/tensor.hpp"
#include "tinyinfer/tensor_io.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

int main()
{
    long long rows{};   
    long long cols{};
    float min{0};
    float max{0};

    std::cout<<"Enter the number of rows: ";
    std::cin>>rows;
    std::cout<<"Enter the number of columns: ";
    std::cin>>cols;
    try
    {
        std::cout<<"Maximum and minimum values of the elements in the tensor: ";
        std::cin>>min;
        std::cin>>max;
        float temp{};
        if(min>max)
        {
            temp=min;
            min=max;
            max=temp;
        }
        
        std::cout<<"Random tensor: "<<'\n';
        tinyinfer::Tensor rmatrix{tinyinfer::random_tensor(rows,cols,min,max)}; //this gives us a new random tensor
        rmatrix.print();

        const std::string path{"data/tensor.txt"};
        tinyinfer::save_tensor_text(rmatrix, path);
        tinyinfer::Tensor loaded_matrix{tinyinfer::load_tensor_text(path)};
        std::cout<<'\n';
        std::cout<<"loaded matrix from "<<path<<" is: "<<'\n';
        
        loaded_matrix.print();

        
        return 0;

    }
    catch(const std::exception& exception) //exception is more general than using runtime_error or out_of_range here
    {
        std::cerr<<"Error: "<<exception.what()<<'\n';
        return 1;
    }
    
}