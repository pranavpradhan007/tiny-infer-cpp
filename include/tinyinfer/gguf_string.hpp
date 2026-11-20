#pragma once

#include <fstream>
#include <string>

namespace tinyinfer
{
    std::string read_gguf_string(std::ifstream& file);
}