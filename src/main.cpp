#include "tinyinfer/tensor.hpp"
#include "tinyinfer/matvec.hpp"
#include "tinyinfer/benchmark.hpp"
#include "tinyinfer/quantized_tensor.hpp"
#include "tinyinfer/quantization.hpp"
#include "tinyinfer/quantization_metrics.hpp"
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
        if (argc != 6)
        {
            throw std::invalid_argument("Usage: tinyinfer <matvec|quantize> --rows <R> --cols <C>");
        }

        std::string command{argv[1]};

        if (command != "matvec" && command != "quantize")
        {
            throw std::invalid_argument("Unknown command: " + command);
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

        
        if(command=="matvec")
        {
            double time{tinyinfer::time_matvec_ms(rows,cols)};
            std::cout<<"\nElapsed time: "<<time<<" ms\n";
        }
        else if(command=="quantize")
        {
            tinyinfer::Tensor tensor{tinyinfer::random_tensor(rows,cols,-1.0f,1.0f)};
            tinyinfer::QuantizedTensor qtensor{tinyinfer::quantize_int8(tensor)};
            tinyinfer::Tensor recovered_tensor{tinyinfer::dequantize_int8(qtensor)};
            float mae{tinyinfer::mean_absolute_error(tensor, recovered_tensor)};
            float max_ae{tinyinfer::max_absolute_error(tensor, recovered_tensor)};
            double comp_ratio{tinyinfer::compression_ratio_fp32_to_int8(tensor)};
            std::cout<<"Dimensions of the original tensor: "<<tensor.rows()<<" X "<<tensor.cols()<<'\n';
            std::cout<<"Dimensions of the recovered tensor: "<<recovered_tensor.rows()<<" X "<<recovered_tensor.cols()<<'\n';
            std::cout<<"FP32 memory: "<<(tensor.raw_data().size()*sizeof(float))/1e6<<" MB"<<'\n';
            std::cout<<"INT8 memory: "<<(qtensor.raw_data().size()*sizeof(std::int8_t))/1e6<<" MB"<<'\n';
            std::cout<<"Quantization scale: "<<qtensor.scale()<<'\n';
            std::cout<<"Mean Absolute Error: "<<mae<<'\n';
            std::cout<<"Maximum Absolute Error: "<<max_ae<<'\n';
            std::cout<<"Compression Ratio: "<<comp_ratio<<" x"<<'\n';
        }
        
        return 0;

    }
    catch(const std::exception& exception) //exception is more general than using runtime_error or out_of_range here
    {
        std::cerr<<"Error: "<<exception.what()<<'\n';
        return 1;
    }
    
}