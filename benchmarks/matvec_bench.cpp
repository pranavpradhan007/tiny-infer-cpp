#include "tinyinfer/benchmark.hpp"
#include "tinyinfer/tensor.hpp"
#include "tinyinfer/matvec.hpp"
#include <chrono>
#include <vector>
#include <iostream>

namespace tinyinfer
{
    double tinyinfer::time_matvec_ms(int rows, int cols)
    {

        float min{-1.0f};
        float max{1.0f};
        std::vector<float> rvector{tinyinfer::random_vector(cols, min, max)};
        std::cout << "Generated random vector: "<< rvector.size() << '\n';
        tinyinfer::Tensor rmatrix{tinyinfer::random_tensor(rows,cols,min,max)};
        std::cout << "Generated random matrix: "<< rmatrix.rows() << " x "<< rmatrix.cols() << '\n';

        std::cout<<'\n'<<"MatVec multipication: "<<'\n';
        const auto start{std::chrono::steady_clock::now()};

        std::vector<float> mresult{tinyinfer::matvec_naive(rmatrix, rvector)};

        const auto finish{std::chrono::steady_clock::now()};

        const std::chrono::duration<double, std::milli> elapsed_milliseconds{finish - start};

        std::cout << "Output size: "<< mresult.size() << '\n';

        std::cout << "First output value: "<< mresult.at(0) << '\n';

        double elapsed{elapsed_milliseconds.count()};

        return elapsed;
    }
}