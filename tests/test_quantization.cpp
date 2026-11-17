#include "tinyinfer/quantized_tensor.hpp"
#include "tinyinfer/tensor.hpp"
#include "tinyinfer/quantization.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <catch2/catch_approx.hpp>


TEST_CASE("INT8 quantization converts FP32 values correctly", "[tensor][shape]")
{
   tinyinfer::Tensor tensor(2,2);
   
   tensor.at(0,0)=-4.0f;
   tensor.at(0,1)=-1.0f;
   tensor.at(1,0)=0.0f;
   tensor.at(1,1)=4.0f;
   tinyinfer::QuantizedTensor qtensor{tinyinfer::quantize_int8(tensor)};
   REQUIRE(qtensor.rows()==2);
   REQUIRE(qtensor.cols()==2);
   REQUIRE(qtensor.scale()==Catch::Approx(4.0f/127.0f));
   REQUIRE(qtensor.raw_data()[0]==-127);
   REQUIRE(qtensor.raw_data()[1]==-32);
   REQUIRE(qtensor.raw_data()[2]==0);
   REQUIRE(qtensor.raw_data()[3]==127);
}

TEST_CASE("FP32 dequantization converts INT8 values correctly", "[quantization][dequantization]")
{
   tinyinfer::Tensor tensor(2,2);
   tensor.at(0,0)=-4.0f;
   tensor.at(0,1)=-1.0f;
   tensor.at(1,0)=0.0f;
   tensor.at(1,1)=4.0f;
   tinyinfer::QuantizedTensor qtensor(tinyinfer::quantize_int8(tensor));
   tinyinfer::Tensor rtensor(tinyinfer::dequantize_int8(qtensor));

   REQUIRE(rtensor.rows() == tensor.rows());
   REQUIRE(rtensor.cols() == tensor.cols());
   float tolerance = qtensor.scale() / 2.0f + 1e-6f;
   for(std::size_t i{0}; i<tensor.raw_data().size(); i++)
   {  
      REQUIRE(rtensor.raw_data()[i]==Catch::Approx(tensor.raw_data()[i]).margin(tolerance));
   }
}



