#include "tinyinfer/tensor.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>


TEST_CASE("Tensor shape: properties are correctly initialized ", "[tensor][shape]")
{
    tinyinfer::Tensor tensor(2,3);
    REQUIRE(tensor.rows()==2);
    REQUIRE(tensor.cols()==3);
    REQUIRE(tensor.size()==6);
}

TEST_CASE("Tensor indexing: elements can be stored and retrieved", "[tensor][indexing]")
{
    tinyinfer::Tensor tensor(2,3);
    tensor.at(1,2)=7.5f;
    REQUIRE(tensor.at(1,2)==7.5f);
}

TEST_CASE("Tensor bounds error: out of bounds access throes an exception", "[tensor][bounds]")
{
    tinyinfer::Tensor tensor(2,3);
    REQUIRE_THROWS_AS(tensor.at(2,0), std::out_of_range);
}