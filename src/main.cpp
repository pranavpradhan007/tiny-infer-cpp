#include <iostream>
#include <string>

using namespace std;

int num_elements(int rows, int columns)     // try to use long long wherever possible
{
    int x;
    x=rows*columns;     // shouldnt have used an intermediate variable to initialize could have directly done return rows*columns;
    return x;
}

int bytes_fp32(int x)
{   
    double z;
    z=x*4;
    return z;
}

double bytes_int8(int x)
{
    return x;
}

int bytes_to_mb(string data_type, int x, const double million)  // no need of datatype here at all as z is returned already with the datatype. (see the if statement in main()).
{
                                                /*
                                                solution should have looked like this:
                                                double bytes_to_mb(long long x, const double million)
                                                {
                                                    return x/million;
                                                }
                                                */
    if (data_type == "fp32")                    
    {   
        double z;
        z=(x*4)/million;
        return z;
    }
    else if (data_type == "int8")
    {
        double z;
        z=x/million;
        return z;
    }
    return 0;
}


int main()
{
    const double million = 1e6; // using constant here is needed for million
    int rows {}; //long long is the right thing to do here as tensors are going to be long very long
    int columns {}; 
    int x;
    string data_type;
    cout<<"Enter the number of rows: ";
    cin>>rows;
    cout<<"Enter the number of columns: ";
    cin>>columns;
    cout<<"Enter the data type: ";
    cin>>data_type;
    
    cout<<"Number of elements: "<<num_elements(rows,columns)<<'\n';
    
    if (data_type == "fp32")
    {
        cout<<"Bytes required: "<<bytes_fp32(num_elements(rows,columns))<<'\n';
        cout<<"MB required: "<<bytes_to_mb(data_type, num_elements(rows,columns), million)<<'\n';
    }

    else if (data_type == "int8")
    {
        cout<<"Bytes required: "<<bytes_int8(num_elements(rows,columns))<<'\n';
        cout<<"MB required: "<<bytes_to_mb(data_type, num_elements(rows,columns), million)<<'\n';
    }
    else
    {
        cout<<"wrong data type! bye bye!";      // there should have been return 1;  after cout
    }
    // cout statements should have been here instead of in the if statements now as we have functions handling calculations
    return 0;
}