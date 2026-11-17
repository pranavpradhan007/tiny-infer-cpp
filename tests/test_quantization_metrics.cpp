#include "tinyinfer/quantization_metrics.hpp"
#include "tinyinfer/quantized_tensor.hpp"
#include "tinyinfer/tensor.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <catch2/catch_approx.hpp>

TEST_CASE("Quantization metrics calculate correct errors","[quantization][metrics]")
{
    tinyinfer::Tensor a(2,2);
    a.at(0,0)=1.0f;
    a.at(0,1)=2.0f;
    a.at(1,0)=3.0f;
    a.at(1,1)=4.0f;
    tinyinfer::Tensor b(2,2);
    b.at(0,0)=1.5f;
    b.at(0,1)=1.5f;
    b.at(1,0)=2.75f;
    b.at(1,1)=5.0f;
    REQUIRE(tinyinfer::mean_absolute_error(a,b)==Catch::Approx(0.5625f));
    REQUIRE(tinyinfer::max_absolute_error(a,b)==1.0f);
    REQUIRE(tinyinfer::compression_ratio_fp32_to_int8(a)==Catch::Approx(4.0f));
}