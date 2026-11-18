
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void write_binary_header()
{
    const char magic[4]{'T', 'I', 'N', 'Y'};
    const std::uint32_t version{1};
    const std::uint64_t count{3};

    std::ofstream outFile("data/tiny_header.bin", std::ios::binary);

    if (!outFile)
    {
        throw std::runtime_error("Could not open file for writing.");
    }

    outFile.write(magic, sizeof(magic));

    outFile.write(
        reinterpret_cast<const char*>(&version),
        sizeof(version)
    );

    outFile.write(
        reinterpret_cast<const char*>(&count),
        sizeof(count)
    );

    if (!outFile)
    {
        throw std::runtime_error("Failed to write binary header.");
    }

    outFile.close();

    if (!outFile)
    {
        throw std::runtime_error("Failed to close output file.");
    }

    std::cout << "Binary file written successfully.\n";
}

void read_binary_header()
{
    const char expectedMagic[4]{'T', 'I', 'N', 'Y'};

    char readmagic[4]{};
    std::uint32_t readversion{};
    std::uint64_t readcount{};

    std::ifstream inFile("data/tiny_header.bin", std::ios::binary);

    if (!inFile)
    {
        throw std::runtime_error("Could not open file for reading.");
    }

    inFile.read(readmagic, sizeof(readmagic));

    inFile.read(
        reinterpret_cast<char*>(&readversion),
        sizeof(readversion)
    );

    inFile.read(
        reinterpret_cast<char*>(&readcount),
        sizeof(readcount)
    );

    if (!inFile)
    {
        throw std::runtime_error("Failed to read complete binary header.");
    }

    if (std::memcmp(readmagic, expectedMagic, sizeof(expectedMagic)) != 0)
    {
        throw std::runtime_error("Invalid binary file magic.");
    }

    if (readversion != 1)
    {
        throw std::runtime_error("Unsupported binary version.");
    }

    if (readcount != 3)
    {
        throw std::runtime_error("Invalid binary count.");
    }

    std::cout << "Binary file read successfully.\n";

    std::cout << "Magic: ";
    std::cout.write(readmagic, sizeof(readmagic));
    std::cout << '\n';

    std::cout << "Version: " << readversion << '\n';
    std::cout << "Count: " << readcount << '\n';
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            throw std::runtime_error("Usage: tinyinfer_binary_demo <write|read>");
        }

        const std::string command{argv[1]};

        if (command == "write")
        {
            write_binary_header();
        }
        else if (command == "read")
        {
            read_binary_header();
        }
        else
        {
            throw std::runtime_error("Unknown command. Use write or read.");
        }

        return 0;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }
}
