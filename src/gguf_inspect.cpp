#include "tinyinfer/gguf_header.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <filesystem>


int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            throw std::runtime_error("Usage: gguf_inspect <path>");
        }

        const std::filesystem::path file_path{argv[1]};

        if (file_path.empty())
        {
            throw std::runtime_error("File path cannot be empty."); 
        }
        
        if (!std::filesystem::is_regular_file(file_path))
        {
            throw std::runtime_error("File not found or is not a regular file: " + file_path.string());
        }

        tinyinfer::GgufHeader header{tinyinfer::parse_gguf_header(file_path.string())};
        std::cout<<"Magic: GGUF\n";
        std::cout<<"Version: "<<header.version<<'\n';
        std::cout<<"Tensor count: "<<header.tensor_count<<'\n';
        std::cout<<"Metadata count: "<<header.metadata_kv_count<<'\n';

        return 0;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }
}