#include <iostream>
#include "tinyinfer/vector_utils.hpp"
#include <vector>
#include <stdexcept>
#include <cmath>


namespace tinyinfer
{
    std::vector<double> create_vector(int n)
    {
        std::vector<double> array{};
        double temp;
        for(int i=0; i<n; i++)
        {
            std::cout<<"Enter "<<i+1<<" element: ";
            std::cin>>temp;
            array.push_back(temp);
        }
        return array;
    }
    
    double sum_vector(const std::vector<double>& array)
    {
        double sum{0};
        for(int i=0; i<array.size(); i++)
        {
            sum+=array[i];
        }
        return sum;
    }
    
    double max_abs(const std::vector<double>& array) 
    {
        if(array.empty())
        {
            throw std::runtime_error("Vector is empty.");
        } 
        double temp_abs;
        temp_abs=std::abs(array[0]);
        
        for(int i=1; i<array.size(); i++)
        {
            if(abs(array[i])>temp_abs)
            {
                temp_abs=std::abs(array[i]);
            }
        }
    
        return temp_abs;
    }
}
