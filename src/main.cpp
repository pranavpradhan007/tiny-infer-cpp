#include "tinyinfer/file_io.hpp"
#include "tinyinfer/memory.hpp"
#include "tinyinfer/vector_utils.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include<vector>

int main()
{
    long long rows {};
    long long columns {};
    std::string data_type {};

    std::cout << "Enter the number of rows: ";
    std::cin >> rows;

    std::cout << "Enter the number of columns: ";
    std::cin >> columns;

    std::cout << "Enter the data type: ";
    std::cin >> data_type;


    // temporary day11 part c declarations
    std::vector<double> array{};
    int n;
    
    



    try
    {
        long long elements {tinyinfer::num_elements(rows, columns)};

        long long bytes {};

        if (data_type == "fp32")
        {
            bytes = tinyinfer::bytes_fp32(elements);
        }
        else if (data_type == "int8")
        {
            bytes = tinyinfer::bytes_int8(elements);
        }
        else
        {
            throw std::runtime_error("unsupported data type");
        }

        std::cout<< "Number of elements: "<< elements<< '\n';

        std::cout<< "Bytes required: "<< bytes<< '\n';

        std::cout<< "MB required: "<< tinyinfer::bytes_to_mb(bytes)<< '\n';

        // Temporary Day 11 Part B test
        const std::string path {"data/vector.txt"};

        std::vector<double> values {tinyinfer::load_vector_text(path)};

        std::cout<< "Loaded "<< values.size()<< " values.\n";

        // Temporary Day 11 Part C test
        std::cout<<"Enter the amount of values in the vector: ";
        std::cin>>n;
        
        array=tinyinfer::create_vector(n);
        std::cout<<"Sum of the elements of the vector is: "<<tinyinfer::sum_vector(array)<<'\n';
        std::cout<<"Maximum absolute of the elements of the vector is: "<<tinyinfer::max_abs(array);

    }
    catch (const std::runtime_error& exception)
    {
        std::cerr<< "Error: "<< exception.what()<< '\n'; ////what() is used for cerr printing with runtime_error() function. what() is a member function of the exception object. It returns the explanatory message stored in the exception.

        return 1;
    }

    return 0;
}