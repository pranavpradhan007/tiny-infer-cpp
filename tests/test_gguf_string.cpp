
#include "tinyinfer/gguf_string.hpp"

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <system_error>

namespace
{
    struct TempFile
    {
        std::filesystem::path path;

        explicit TempFile(const std::string& name)
            : path(std::filesystem::temp_directory_path() /
                   ("tinyinfer_gguf_" + name + ".bin"))
        {
        }

        ~TempFile()
        {
            std::error_code error;
            std::filesystem::remove(path, error);
        }
    };

    void write_test_string(const std::filesystem::path& path,std::uint64_t declared_length,const std::string& data,std::size_t prefix_bytes = 8)
    {
        std::ofstream outFile(path,std::ios::binary | std::ios::trunc);

        if (!outFile)
        {
            throw std::runtime_error("Could not create test file.");
        }

        for (std::size_t i = 0; i < prefix_bytes; ++i)
        {
            const char byte = static_cast<char>((declared_length >> (8 * i)) & 0xFF);
            outFile.put(byte);
        }

        outFile.write(data.data(),static_cast<std::streamsize>(data.size()));

        outFile.close();

        if (!outFile)
        {
            throw std::runtime_error("Failed to write test file.");
        }
    }
}

TEST_CASE("GGUF string reader", "[gguf][string]")
{
    SECTION("Normal string")
    {
        TempFile temp{"normal"};

        write_test_string(temp.path, 12, "general.name");

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        const std::string result =
            tinyinfer::read_gguf_string(inFile);

        REQUIRE(result == "general.name");
        REQUIRE(result.size() == 12);
    }

    SECTION("Short string")
    {
        TempFile temp{"short"};

        write_test_string(temp.path, 3, "cat");

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        REQUIRE(tinyinfer::read_gguf_string(inFile) == "cat");
    }

    SECTION("Empty string")
    {
        TempFile temp{"empty"};

        write_test_string(temp.path, 0, "");

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        const std::string result =tinyinfer::read_gguf_string(inFile);

        REQUIRE(result.empty());
    }

    SECTION("Truncated length prefix")
    {
        TempFile temp{"truncated_prefix"};

        write_test_string(temp.path, 12, "", 4);

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        REQUIRE_THROWS_AS(tinyinfer::read_gguf_string(inFile),std::runtime_error);
    }

    SECTION("Truncated string data")
    {
        TempFile temp{"truncated_data"};

        write_test_string(temp.path, 10, "cat");

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        REQUIRE_THROWS_AS(tinyinfer::read_gguf_string(inFile),std::runtime_error);
    }

    SECTION("String exceeds 1 MiB")
    {
        TempFile temp{"oversized"};

        write_test_string(temp.path, 1048577, "");

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        REQUIRE_THROWS_AS(tinyinfer::read_gguf_string(inFile),std::runtime_error);
    }

    SECTION("Embedded null byte")
    {
        TempFile temp{"embedded_null"};

        const std::string original{"A\0B", 3};

        write_test_string(temp.path, 3, original);

        std::ifstream inFile(temp.path, std::ios::binary);
        REQUIRE(inFile.is_open());

        const std::string result = tinyinfer::read_gguf_string(inFile);

        REQUIRE(result.size() == 3);
        REQUIRE(result == original);
        REQUIRE(result[1] == '\0');
    }
}
