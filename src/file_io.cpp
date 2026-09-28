#include "tinyinfer/file_io.hpp"

#include <fstream>
#include <stdexcept>

namespace tinyinfer
{
    void save_vector_text(const std::string& path, const std::vector<double>& values)
    {
        std::ofstream output_file {path};

        if (!output_file)
        {
            throw std::runtime_error("could not open file for writing: " + path); //directly throw instead of using try here.
        }

        for (double value : values)
        {
            output_file << value << '\n';
        }
    }

    std::vector<double> load_vector_text(const std::string& path)
    {
        std::ifstream input_file {path};

        if (!input_file)
        {
            throw std::runtime_error("could not open file for reading: " + path);
        }

        std::vector<double> values {};
        double value {};

        while (input_file >> value)
        {
            values.push_back(value);
        }

        return values;
    }
}