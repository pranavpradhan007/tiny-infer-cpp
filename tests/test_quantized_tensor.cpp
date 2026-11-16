#include "tinyinfer/quantized_tensor.hpp"
#include <limits>
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <catch2/catch_approx.hpp>

TEST_CASE("Quantized Tensor shape: properties are correctly initialized ", "[tensor][shape]")
{
    tinyinfer::QuantizedTensor qtensor(2,3,0.01f);
    REQUIRE(qtensor.rows()==2);
    REQUIRE(qtensor.cols()==3);
    REQUIRE(qtensor.scale()==Catch::Approx(0.01f));
}

TEST_CASE("QuantizedTensor rejects invalid constructor arguments","[tensor][shape]")
{
    REQUIRE_THROWS_AS(tinyinfer::QuantizedTensor(0,3,0.01f), std::invalid_argument);
    REQUIRE_THROWS_AS(tinyinfer::QuantizedTensor(2,-1,0.01f), std::invalid_argument);
    REQUIRE_THROWS_AS(tinyinfer::QuantizedTensor(2,3,0.0f), std::invalid_argument);
    REQUIRE_THROWS_AS(tinyinfer::QuantizedTensor(2,3,-0.01f), std::invalid_argument);
    REQUIRE_THROWS_AS(tinyinfer::QuantizedTensor(2,3,std::numeric_limits<float>::quiet_NaN()), std::invalid_argument);
    REQUIRE_THROWS_AS(tinyinfer::QuantizedTensor(2,3,std::numeric_limits<float>::infinity()), std::invalid_argument);
}


