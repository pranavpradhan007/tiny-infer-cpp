#include "tinyinfer/memory.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    const double million = 1e6; 
    long long rows {};
    long long columns {}; 
    string data_type;
    cout<<"Enter the number of rows: ";
    cin>>rows;
    cout<<"Enter the number of columns: ";
    cin>>columns;

    if (rows <= 0 || columns <= 0)
    {
        cerr << "Rows and columns must be positive.\n";
        return 1;
    }

    cout<<"Enter the data type: ";
    cin>>data_type;
    long long elements{num_elements(rows,columns)};
    cout<<"Number of elements: "<<elements<<'\n';
    
    if (data_type == "fp32")
    {
        cout<<"Bytes required: "<<bytes_fp32(elements)<<'\n';
        cout<<"MB required: "<<bytes_to_mb(bytes_fp32(elements), million)<<'\n';
    }

    else if (data_type == "int8")
    {
        cout<<"Bytes required: "<<bytes_int8(elements)<<'\n';
        cout<<"MB required: "<<bytes_to_mb(elements, million)<<'\n';
    }
    else
    {
        cerr<<"wrong data type! bye bye!";      
        return 1;
    }

    return 0;
}