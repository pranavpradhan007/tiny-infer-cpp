#include "tinyinfer/tensor.hpp"
// #include "tinyinfer/tensor_io.hpp"
#include "tinyinfer/matvec.hpp"
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
    int size{};

    std::cout<<"Enter the number of rows: ";
    std::cin>>rows;
    std::cout<<"Enter the number of columns: ";
    std::cin>>cols;
    try
    {
        std::cout<<'\n';
        std::cout<<"Enter the size of the vector: ";
        std::cin>>size;
        std::cout<<"Maximum and minimum values of the elements in the tensor and vector: ";
        std::cin>>min;
        std::cin>>max;
        float temp{};
        if(min>max)
        {
            temp=min;
            min=max;
            max=temp;
        }
        std::vector<float> rvector{tinyinfer::random_vector(size, min, max)};
        std::cout<<"Random vector: "<<'\n';
        for(const auto& element: rvector)
        {
            std::cout<<element<<" ";
        }
        std::cout<<'\n';
        
        std::cout<<"Random tensor: "<<'\n';
        tinyinfer::Tensor rmatrix{tinyinfer::random_tensor(rows,cols,min,max)};
        rmatrix.print();
        
        std::cout<<'\n'<<"MatVec multipication: "<<'\n';
        std::vector<float> mresult{tinyinfer::matvec_naive(rmatrix, rvector)};
        for(const auto& element: mresult)
        {
            std::cout<<element<<" ";
        }
        
        return 0;

    }
    catch(const std::exception& exception) //exception is more general than using runtime_error or out_of_range here
    {
        std::cerr<<"Error: "<<exception.what()<<'\n';
        return 1;
    }
    
}