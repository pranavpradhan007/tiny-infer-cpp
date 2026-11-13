# Day 36 - INT8 Quantization Theory

## What is quantization, and how is FP32 different from INT8?

Quantization converts high-precision numerical values, such as FP32, into a lower-precision representation, such as INT8.

FP32 uses 32 bits (4 bytes) per value, while INT8 uses 8 bits (1 byte). Therefore, storing the same number of values as INT8 instead of FP32 reduces the raw storage requirement by approximately 4×.

This reduces the memory footprint and can decrease memory bandwidth requirements and energy consumption. However, quantization introduces numerical approximation errors, and the actual performance benefits depend on hardware and implementation.

## What does the quantization scale represent, and why do we divide by 127?

The quantization scale determines how values in the original floating-point range are mapped to discrete INT8 values.

For symmetric signed INT8 quantization, we calculate:
\[
s=\frac{\max |x|}{127}
\]

We divide by 127 because it is the maximum positive value representable by a signed 8-bit integer.

Although the signed INT8 range is −128 to 127, symmetric quantization commonly uses −127 to 127 so that positive and negative magnitudes are represented equally.

For example, if the maximum absolute floating-point value is 1.0:
\[
s=\frac{1}{127}\approx0.007874
\]

This means each integer step corresponds to approximately 0.007874 in the original floating-point representation.

## What is dequantization, and why might the recovered number differ from the original?

Dequantization reconstructs an approximate floating-point value from its quantized integer representation.
\[
x_{\text{recovered}}=q\times s
\]

The recovered value may differ from the original because quantization rounds continuous floating-point values to a limited set of integer levels. The lost precision generally cannot be recovered.

## What is quantization error, and why does it matter for AI model accuracy?

Quantization error is the difference between the original floating-point value and the value recovered after quantization and dequantization.
\[
e=|x-x_{\text{recovered}}|
\]

Because INT8 represents fewer distinct values than FP32 over a typical chosen range, multiple floating-point values may map to the same integer.

In neural networks, quantization errors in weights or activations can propagate through linear operations and nonlinear activation functions. These errors may affect intermediate computations, predictions, and ultimately model accuracy.

The amount of accuracy loss depends on the model architecture, data distribution, quantization scheme, and precision sensitivity of different operations.

## What is the theoretical compression ratio of FP32 to INT8, and does this guarantee a 4× speedup?

FP32 requires 4 bytes per value, while INT8 requires 1 byte.

Therefore, the theoretical raw storage compression ratio is:
\[
\frac{4}{1}=\boxed{4:1}
\]

However, a 4× reduction in storage does not guarantee a 4× increase in execution speed.

Performance depends on hardware support for INT8 operations, memory bandwidth, quantization and dequantization overhead, and whether the workload is compute-bound or memory-bound.

A model may also retain certain operations in higher precision, and scale factors require additional storage.

Therefore, quantization can substantially reduce memory consumption without necessarily producing an equivalent computational speedup.





# Day 37 - 