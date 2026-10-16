#include "tinyinfer/tensor.hpp"
#include "tinyinfer/matvec.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <vector>

TEST_CASE("Known MatVec output: matrix-vector multiplication produces exact expected results", "[matvec][math]")
{
    tinyinfer::Tensor tensor(2,3);
    tensor.at(0,0)=1.0f;
    tensor.at(0,1)=2.0f;
    tensor.at(0,2)=3.0f;
    tensor.at(1,0)=4.0f;
    tensor.at(1,1)=5.0f;
    tensor.at(1,2)=6.0f;

    std::vector<float> vec(3);
    vec[0]=10.0f;
    vec[1]=20.0f;
    vec[2]=30.0f;

    std::vector<float> result{tinyinfer::matvec_naive(tensor, vec)};
    REQUIRE(result.size()==2);
    REQUIRE(tinyinfer::almost_equal(result[0], 140.0f));
    REQUIRE(tinyinfer::almost_equal(result[1], 320.0f));
}

TEST_CASE("Dimension mismatch: incompatible matrix and vector shapes throw runtime error","[matvec][bounds]")
{
    tinyinfer::Tensor tensor(2,3);
    std::vector<float> vec(2);
    REQUIRE_THROWS_AS(tinyinfer::matvec_naive(tensor, vec), std::runtime_error);
}