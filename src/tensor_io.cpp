#include "tinyinfer/tensor_io.hpp"
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>

namespace tinyinfer
{
    void tinyinfer::save_tensor_text(const Tensor& tensor, const std::string& path)
    {
        std::ofstream outf{path};
        if(!outf)
        {
            throw std::runtime_error("File cannot be opened!");
        }
        outf<<tensor.rows()<<" ";
        outf<<tensor.cols()<<'\n';
        const std::vector<float>& data{tensor.raw_data()};

        for(auto& element:data)
        {
            outf<<element<<" ";
        }
    }

    tinyinfer::Tensor tinyinfer::load_tensor_text(const std::string& path)
    {
        std::ifstream inf{path};
        if(!inf)
        {
            throw std::runtime_error("File cannot be opened!");
        }
        long long rows{};
        long long cols{};

        inf>>rows>>cols; //first put rows and cols from the text file 
        tinyinfer::Tensor ltensor{rows, cols}; 
        std::vector<float>& data{ltensor.raw_data()}; //data initally would be rowsxcolumns all 0 initailized
        for(auto& element : data)
        {
            inf>>element;//now only thing remains in the buffer would be the data as we already extracted the rows and columns from the file
        }

        return ltensor;  
    }
}