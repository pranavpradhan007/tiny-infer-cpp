#pragma once

#include <cstdint>
#include <string>

namespace tinyinfer
{
    struct GgufHeader
    {
        std::uint32_t magic{};
        std::uint32_t version{};
        std::uint64_t tensor_count{};
        std::uint64_t metadata_kv_count{};
    };

    GgufHeader parse_gguf_header(const std::string& path);
}