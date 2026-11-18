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





# Day 37 - Implementing the QuantizedTensor Class

## Q1. What is the purpose of the QuantizedTensor class?

QuantizedTensor is a class designed to store quantized tensor data using signed 8-bit integers. It maintains the tensor's shape, scale, and underlying data. Unlike the original FP32 Tensor, it uses less memory per element and requires a quantization scale to interpret the stored integers.

## Why do we use std::vector<std::int8_t> to store quantized data?

We use std::vector<std::int8_t> because it provides contiguous, dynamically sized INT8 storage and manages memory automatically through RAII. This reduces the risk of memory leaks and makes tensor storage safer and easier to manage.

## Why does QuantizedTensor need to store a scale_ value?

The scale represents how much of the original floating-point range corresponds to one quantized integer step. It is needed for both quantization and dequantization. Without the scale, we cannot determine the approximate original floating-point values from the stored INT8 values.

## Why are rows(), cols(), and scale() declared as const member functions?

We declare rows(), cols(), and scale() as const member functions because they should only return stored information without modifying the object's state. This improves const-correctness and allows the functions to be called on constant objects.

## Why must the constructor validate its inputs?

Constructor validation ensures that every successfully constructed QuantizedTensor starts in a valid state. By rejecting invalid dimensions and scales immediately, we prevent incorrect objects from being used later and avoid requiring every caller to repeat the same validation.

## Why did we use std::size_t and check data_.max_size() / c before allocating memory?

We use std::size_t because it is the standard unsigned type for representing sizes in C++. We check data_.max_size() / c before multiplication to ensure that the requested number of elements is within the vector's supported limit and that calculating the element count is safe.





# Day 38 - Implementing INT8 Quantization in C++

## Explain the complete flow of quantize_int8().

`quantize_int8()` rejects invalid dimensions and non-finite values, sets the scale to the largest absolute value divided by 127 (or 1 if the tensor is all zeros), and stores each float as `round(value / scale)` clamped to `[-127, 127]`. It returns a `QuantizedTensor` with the same shape, that scale, and those INT8 values.

## Why do we use the maximum absolute value when calculating the quantization scale?

to map the entire continuous data range into the fixed bounds of a lower-precision integer format without clipping or information loss

## Why are rounding, clamping, and special-case handling necessary?

Rounding is necessary because `value / scale` is a float, and INT8 storage needs the nearest integer. Clamping keeps that integer inside `[-127, 127]`, and the special cases avoid a scale of `0` when the tensor is all zeros or the computed scale underflows.

## How does INT8 quantization contribute to AI inference optimization?

INT8 quantization stores each value in 1 byte instead of 4, so weights and activations use about one quarter of the memory and move less data during inference. That can make inference faster and cheaper on hardware with INT8 support, though the speedup is not automatically 4× because of dequantization overhead and operations that stay in higher precision.





# Day 39 - Implementing INT8 Dequantization in C++

## Is dequantization mathematically reversible?

dequantization is generally not mathematically reversible as quantization is a lossy operation.

## Is the maximum dequantization error always half the quantization scale?

No  the maximum dequantization error is not always bounded by \(\frac{s}{2}\). That bound only holds strictly inside the representable dynamic range of a uniform quantizer using pure round-to-nearest rounding.
In practice, hardware constraints, clipping, and asymmetric formats frequently cause the error to exceed \(\frac{s}{2}\).

## Can we directly compare or add INT8 values from tensors with different quantization scales?

No, you cannot directly compare or add INT8 values from tensors that have different quantization scales. Because each stored integer is merely a compressed representation multiplied by its own scaling factor, operating on the raw integers ignores their true real-world magnitudes.

## Do we always need to dequantize before performing matrix multiplication?

No, you do not need to dequantize matrices before performing matrix multiplication. You can compute the matrix product directly in integer arithmetic and apply a single floating-point scaling step afterward.





# Day 40 - Quantization Error Metrics

## Can two quantization methods have the same MAE but different maximum errors?

Yes, two quantization methods can easily have the same Mean Absolute Error (MAE) while having completely different maximum errors. Because MAE averages the absolute errors across all values in a tensor or dataset, one large outlier error can be masked if the remaining values have very small errors.

## Why can a model have low quantization error but still lose significant prediction accuracy?

A model can have very low quantization error (small numerical distance between original and quantized weights) yet suffer a severe drop in task prediction accuracy due to how neural networks process information non-linearly and accumulate errors.

## Are MAE and maximum absolute error sufficient to evaluate a quantized AI model?

No, Mean Absolute Error (MAE) and Maximum Absolute Error are not sufficient on their own to evaluate a quantized AI model. While they are useful for verifying low-level numerical accuracy during kernel development, they miss critical downstream impacts on model behavior and compound errors across layers.

## Why is a 4× theoretical compression ratio different from the actual memory savings of an inference system?

A 4× theoretical compression ratio (such as moving from 16-bit to 4-bit weights) rarely translates to a 4× reduction in total system memory for an AI inference engine due to several fixed architectural overheads and runtime allocations.





# Day 41 - Quantization CLI

## Why should the CLI be separate from the numerical computation library?

Separating the Command-Line Interface (CLI) from the numerical computation library ensures reusability, easier testing, and clean maintainability. This software design principle, known as separation of concerns, keeps user interaction logic decoupled from core math operations.

## Why is reproducibility important when benchmarking AI optimization techniques?

Reproducibility is essential when benchmarking AI optimization techniques because it ensures that measured speedups or efficiency gains come from your actual code changes rather than random noise or environmental shifts. Without a consistent baseline, you cannot verify whether an optimization truly improves performance or if a regression has been introduced.

## Why is input validation especially important in a command-line tool that allocates memory?

Input validation is critical in a command-line tool that allocates memory because untrusted arguments can directly trigger crashes, resource exhaustion, or severe security vulnerabilities. When a program blindly uses user-provided numbers or strings to request memory from the operating system, a simple typo or malicious input can break the application.

## What makes a CLI experiment scientifically meaningful?

A command-line interface (CLI) experiment is scientifically meaningful when it produces reproducible, verifiable, and unbiased evidence that isolates how specific inputs or configurations affect system behavior.
Rather than simply running a script and observing a single output, a rigorous CLI experiment controls the execution environment so other researchers can independently verify the results and draw valid conclusions.





# Day 42 - Week 6 Review

## Numerical reasoning: You have two FP32 tensors: A = [−1.0, −0.5, 0, 0.5, 1.0] and B = [−1.0, −0.5, 0, 0.5, 100.0]. Both use symmetric per-tensor INT8 quantization. Explain how the large outlier in B changes the scale, what happens to the smaller values, and why B might have worse reconstruction quality for those values. Calculate the scale for both tensors.

In symmetric per-tensor INT8 quantization, the scale factor is determined by dividing the tensor's maximum absolute value by 127, which gives Tensor A a fine-grained scale of 0.007874 (\(1.0 / 127\)) and stretches Tensor B's scale by 100× to 0.787402 (\(100.0 / 127\)) to accommodate its 100.0 outlier. Because the scale acts as the step size between representable integers, Tensor B's massive step size squeezes all smaller values between \(-1.0\) and \(0.5\) into just three integer buckets (\(-1\), \(0\), and \(1\)). Consequently, distinct numbers like \(-1.0\) and \(-0.5\) collapse into the same quantized integer (\(-1\)) and dequantize back to \(-0.7874\), causing severe rounding errors and poor reconstruction quality compared to Tensor A, which reconstructs those same values within 0.004 of their original precision.

## Error versus model behavior: Two quantization strategies produce the same MAE. Strategy A has uniformly small errors; Strategy B has one much larger error in an important neural-network weight. Which would you prefer, and why? Can MAE and maximum error alone determine the better strategy? Explain how you would evaluate their actual model impact.

Strategy A is strongly preferred because neural networks easily tolerate small, uniform perturbations that tend to cancel out during matrix multiplications, whereas a single large error in a critical weight can trigger severe activation spikes and distort nonlinear thresholds across downstream layers. Mean Absolute Error (MAE) and maximum error alone cannot determine the better strategy because they treat all weights as equally important, ignoring weight sensitivity (saliency) and how weight errors interact with actual input activations. To evaluate true model impact, you must run a calibration or test dataset through both the original and quantized models to measure end-to-end behavioral changes—specifically tracking output distribution divergence (such as KL divergence on logits), layer-wise activation error, and downstream task metrics like perplexity or accuracy.

## Memory and performance: Suppose your AI inference system uses 800 MB of FP32 weights and 200 MB of other runtime memory. You quantize only the weights to INT8, reducing their raw storage by 4×, while other memory remains unchanged. Calculate the new total memory, the overall compression ratio, and the percentage reduction. Then explain why execution time might not decrease proportionally.

Quantizing the 800 MB of FP32 weights to INT8 shrinks them by 4× to 200 MB. Combined with the unchanged 200 MB of runtime memory, the new total memory is 400 MB, which yields an overall compression ratio of 2.5× and a 60% total memory reduction. However, execution time rarely drops proportionally because weight-only quantization (W8A32 or W8A16) introduces dequantization overhead, forcing the hardware to cast INT8 weights back to floating-point on the fly before computing. Additionally, unquantized runtime buffers like activations and KV caches still transfer at full precision, non-matrix operations such as LayerNorm and Softmax remain unaccelerated under Amdahl's Law, and compute-bound workloads or hardware lacking native mixed-precision tensor cores cannot convert smaller weight footprints directly into proportional speedups.

## System design and reliability: Imagine Tiny Infer is becoming a real inference engine. A developer wants to delete the QuantizedTensor class, use std::vector<int8_t> everywhere, and move quantization and error calculations directly into main.cpp. Evaluate the design. What information and guarantees would be lost, what maintenance or testing problems could arise, and how would this affect future optimization experiments?

Deleting the QuantizedTensor class in favor of raw std::vector<int8_t> buffers and moving logic into main.cpp is a poor architectural choice that sacrifices type safety, modularity, and extensibility. Using a raw byte vector strips away essential metadata like quantization scales, zero-points, tensor dimensions, and memory alignment, forcing developers to pass loose variables across functions and inviting silent numerical bugs or out-of-bounds errors. Moving quantization and error calculations directly into main.cpp also makes the core math impossible to link into unit test suites, encourages copy-pasting across layers, and bloats the entry point with low-level implementation details. Finally, hardcoding std::vector<int8_t> across the codebase blocks future optimization experiments, as upgrading to per-channel scales, INT4 bit-packing, or SIMD-aligned hardware kernels would require rewriting every function signature instead of cleanly extending a single class interface.