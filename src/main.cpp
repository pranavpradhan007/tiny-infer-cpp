#include <iostream>
#include <string>

using namespace std;

int main()
{
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
    
    x=rows*columns;
    cout<<"Number of elements: "<<x<<'\n';
    
    if (data_type == "fp32")
    {
        cout<<"Bytes required: "<<x*4<<'\n';
        cout<<"MB required: "<<(x*4)/1e6<<'\n';
    }

    else if (data_type == "int8")
    {
        cout<<"Bytes required: "<<x<<'\n';
        cout<<"MB required: "<<x/1e6<<'\n';
    }
    else
    {
        cout<<"wrong data type! bye bye!";
    }

    return 0;
}