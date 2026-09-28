#pragma once

namespace tinyinfer
{
    long long num_elements(long long rows, long long columns);

    long long bytes_fp32(long long elements);

    long long bytes_int8(long long elements);

    double bytes_to_mb(long long bytes);
}