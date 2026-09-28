#pragma once
#include <string>
#include <vector>
namespace tinyinfer
{
    void save_vector_text(const std::string& , const std::vector<double>& );
    std::vector<double> load_vector_text(const std::string& );
}
