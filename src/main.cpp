#include "tinyinfer/tensor.hpp"
#include "tinyinfer/matvec.hpp"
#include "tinyinfer/benchmark.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

int main(int argc , char* argv[])
{
    long long rows{};   
    long long cols{};
    
    bool rows_found{false};
    bool cols_found{false};
    try
    {
        if(argc!=6 || std::string(argv[1])!="matvec")
        {
            throw std::invalid_argument("Usage: tinyinfer matvec --rows <R> --cols <C>");
        }

        for(int i{2}; i<argc; i++)
        {
            std::string arg= argv[i];
            if(arg=="--rows")
            {
                if(rows_found||i+1 >= argc)
                {
                    throw std::invalid_argument("Missing or duplicate --rows argument");
                }
                std::string value{argv[++i]};
                std::size_t pos{0};

                rows = std::stoll(value, &pos);  //string to long long 
                if(pos!= value.size())
                {
                    throw std::invalid_argument("Rows must be a valid integer");
                }
                rows_found=true;
            }
            else if (arg=="--cols")
            {
                if (cols_found || i + 1 >= argc)
                {
                    throw std::invalid_argument("Invalid or duplicate --cols argument");
                }
                std::string value{argv[++i]};
                std::size_t pos{0};

                cols = std::stoll(value, &pos);

                if (pos != value.size())
                {
                    throw std::invalid_argument("Columns must be a valid integer");
                }

                cols_found = true;
            }
            else
            {
                throw std::invalid_argument("Unknown argument: " + arg);
            }
        }

        if (!rows_found || !cols_found)
        {
            throw std::invalid_argument("Both --rows and --cols are required");
        }

        if (rows <= 0 || cols <= 0)
        {
            throw std::invalid_argument("Rows and columns must be positive");
        }

        constexpr long long max_dimension{4096};

        if (rows > max_dimension || cols > max_dimension)
        {
            throw std::invalid_argument("Matrix dimensions must not exceed 4096");
        }

        double time{tinyinfer::time_matvec_ms(rows,cols)};

        std::cout<<"\nElaspsed time: "<<time<<" ms\n";
        
        return 0;

    }
    catch(const std::exception& exception) //exception is more general than using runtime_error or out_of_range here
    {
        std::cerr<<"Error: "<<exception.what()<<'\n';
        return 1;
    }
    
}