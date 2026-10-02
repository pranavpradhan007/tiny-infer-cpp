#include "tinyinfer/tensor.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{
    long long rows{};   
    long long cols{};
    int row{};
    int col{};
    float changed_element{};
    float fill_elements{};
    
    float sum{0};

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
        std::cout<<"What should be the matrix initialised with today?: ";
        std::cin>>fill_elements;
        matrix.fill(fill_elements);
        std::cout<<"Initialized matrix: \n";
        matrix.print();

        std::cout<<'\n';
        const std::vector<float>& data{matrix.raw_data()};
        
        for(auto element : data)
        {
            sum+=element;
        }
        std::cout<<"sum of the elements in the tensor is: "<<sum<<'\n';

        // std::cout<<"Change the element in row, col. \nEnter row and column here: ";
        // std::cin>>row>>col;
        // std::cout<<"Change the value here: ";
        // std::cin>>changed_element;
        // matrix.at(row,col)=changed_element;
        // std::cout<<"After changing the element the matrix is: \n";
        // matrix.print();

        return 0;

    }
    catch(const std::exception& exception) //exception is more general than using runtime_error or out_of_range here
    {
        std::cerr<<"Error: "<<exception.what()<<'\n';
        return 1;
    }
    
}