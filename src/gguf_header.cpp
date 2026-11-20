#include "tinyinfer/gguf_header.hpp"

#include <cstdint>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstring>


namespace tinyinfer
{
    GgufHeader parse_gguf_header(const std::string& path)
    {
        GgufHeader header{};

        std::ifstream infile(path, std::ios::binary);

        if (!infile)
        {
            throw std::runtime_error("Could not open file for reading.");
        }

        infile.read(reinterpret_cast<char*>(&header.magic),sizeof(header.magic));
        infile.read(reinterpret_cast<char*>(&header.version),sizeof(header.version));
        infile.read(reinterpret_cast<char*>(&header.tensor_count),sizeof(header.tensor_count));
        infile.read(reinterpret_cast<char*>(&header.metadata_kv_count),sizeof(header.metadata_kv_count));

        if (!infile)
        {
            throw std::runtime_error("Failed to read complete gguf header.");
        }
        const char expectedMagic[4]{'G', 'G', 'U', 'F'};
        if (std::memcmp(&header.magic, expectedMagic, sizeof(expectedMagic)) != 0)
        {
            throw std::runtime_error("Invalid gguf file magic.");
        }

        if (header.version != 3)
        {
            throw std::runtime_error("Unsupported gguf version.");
        }

        return header;
    }
}