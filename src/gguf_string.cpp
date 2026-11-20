#include "tinyinfer/gguf_string.hpp"

#include <fstream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <limits>

namespace tinyinfer
{
    std::string read_gguf_string(std::ifstream& file)
    {
        std::uint64_t len{0};


        if (!file)
        {
            throw std::runtime_error("Could not open file for reading.");
        }

        file.read(reinterpret_cast<char*>(&len),sizeof(std::uint64_t));

        if (!file)
        {
            throw std::runtime_error("Failed to read GGUF string length.");
        }

        if(len>1048576)
        {
            throw std::runtime_error("Length is greater than 1MiB.");
        }

        std::string result{};
        if(len>result.max_size() || len>std::numeric_limits<std::streamsize>::max())
        {
            throw std::runtime_error("Length is greater than standard sizes.");
        }

        if (len==0)
        {
            return {};
        }


        result.resize(static_cast<std::size_t>(len));

        file.read(result.data(), static_cast<std::streamsize>(len));

        if (!file)
        {
            throw std::runtime_error("Failed to read GGUF string data.");
        }        

        return result;
    }
}