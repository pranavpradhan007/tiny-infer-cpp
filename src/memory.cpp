#include "tinyinfer/memory.hpp"

long long num_elements(long long rows, long long columns)     
{
    return rows*columns;
}

long long bytes_fp32(long long elements)
{   
    return elements*4;
}

long long bytes_int8(long long elements)
{
    return elements;
}

double bytes_to_mb(long long elements, const double million) 
{
    return elements/million;
}