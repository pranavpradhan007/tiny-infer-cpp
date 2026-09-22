#include <iostream>
#include <string>

using namespace std;

struct TensorShape
{
    long long rows{};
    long long cols{};   
};

long long num_elements(const TensorShape& shape)
{
    return {shape.rows * shape.cols};
}

string print_shape(const TensorShape& shape)
/*could have done something simpler:
string print_shape(const TensorShape& shape)
{
    return "Tensor Shape is " +
           to_string(shape.rows) +
           " X " +
           to_string(shape.cols);
}
*/
{
    string message;
    string row_str;
    string col_str;
    row_str=to_string(shape.rows);
    col_str=to_string(shape.cols);
    message="Tensor Shape is " + row_str + " X " + col_str;
    return message;
}

bool is_valid_shape(const TensorShape& shape) 
/* could have done something like this:
bool is_valid_shape(const TensorShape& shape)
{
    return shape.rows > 0 && shape.cols > 0;
}

*/
{
    if(shape.rows>0 && shape.cols>0){
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    TensorShape shape{};
    cout<<"Enter number of rows: ";
    cin>>shape.rows;
    cout<<"Enter number of cols: ";
    cin>>shape.cols;
    if(is_valid_shape(shape)==false)
    {
        cout<<"Error, tensor cannot have 0 rows, 0 columns. bye bye";
        return 1;
    }
    cout<<"The tensor is valid."<<endl;

    long long n{num_elements(shape)};
    cout<<"The number of elements in the tensor are: "<<n<<'\n';
    string shape_str{print_shape(shape)};
    cout<<shape_str;

    return 0;
}