#include "tinyinfer/matvec.hpp"
#include "tinyinfer/tensor.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{

    {
        tinyinfer::Tensor matrix{2, 3};

        matrix.at(0, 0) = 1.0f;
        matrix.at(0, 1) = 2.0f;
        matrix.at(0, 2) = 3.0f;

        matrix.at(1, 0) = 4.0f;
        matrix.at(1, 1) = 5.0f;
        matrix.at(1, 2) = 6.0f;

        std::vector<float> vector{10.0f, 20.0f, 30.0f};

        std::vector<float> result{
            tinyinfer::matvec_naive(matrix, vector)
        };

        assert(result.size() == 2);
        assert(tinyinfer::almost_equal(result[0], 140.0f));
        assert(tinyinfer::almost_equal(result[1], 320.0f));
    }


    {
        tinyinfer::Tensor matrix{1, 1};

        matrix.at(0, 0) = 5.0f;

        std::vector<float> vector{3.0f};

        std::vector<float> result{
            tinyinfer::matvec_naive(matrix, vector)
        };

        assert(result.size() == 1);
        assert(tinyinfer::almost_equal(result[0], 15.0f));
    }

    {
        tinyinfer::Tensor matrix{2, 2};

        std::vector<float> vector{5.0f, -3.0f};

        std::vector<float> result{
            tinyinfer::matvec_naive(matrix, vector)
        };

        assert(result.size() == 2);
        assert(tinyinfer::almost_equal(result[0], 0.0f));
        assert(tinyinfer::almost_equal(result[1], 0.0f));
    }

    {
        tinyinfer::Tensor matrix{2, 2};

        matrix.at(0, 0) = 1.0f;
        matrix.at(0, 1) = 0.0f;
        matrix.at(1, 0) = 0.0f;
        matrix.at(1, 1) = 1.0f;

        std::vector<float> vector{5.0f, 8.0f};

        std::vector<float> result{
            tinyinfer::matvec_naive(matrix, vector)
        };

        assert(result.size() == 2);
        assert(tinyinfer::almost_equal(result[0], 5.0f));
        assert(tinyinfer::almost_equal(result[1], 8.0f));
    }

    {
        tinyinfer::Tensor matrix{2, 3};

        std::vector<float> vector{10.0f, 20.0f};

        bool exception_thrown{false};

        try
        {
            tinyinfer::matvec_naive(matrix, vector);
        }
        catch (const std::runtime_error&)
        {
            exception_thrown = true;
        }

        assert(exception_thrown);
    }

    std::cout << "All MatVec tests passed!\n";

    return 0;
}