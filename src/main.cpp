#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void save_vector_text(const string& path, const vector<double>& array)
{
    ofstream outf{path};
    if(!outf)
    {
        cerr<<"vector.txt cannot be opened for writing!";
        return;
    }
    for(int i =0; i<array.size(); i++) // for(double i : array) basically for i in array from python
    {
        outf<<array[i]<<"\n";
    }
}

vector<double> load_vector_text(const string& path)
{
    ifstream inf{path};
    if(!inf)
    {
        cerr<<"vector.txt cannot be opened for reading!";
        return {}; 
    }
    vector<double> array{};
    double value;
    while(inf>>value)
    {
        array.push_back(value);
    }

    return array;

}

int main()
{
    int n{};
    cout<<"How many values for the vector: ";
    cin>>n;
    double temp{};
    vector<double> array;
    if(n<=0)
    {
        cerr<<"Wrong input, values of vector must be > 0.";
        return 1;
    }
    for(int i=0; i<n; i++)
    {
        cout<<"Enter the "<<i<<" value of the vector: ";
        cin>>temp;
        array.push_back(temp);
    }
    const string path{"data/vector.txt"};
    save_vector_text(path, array);
    array=load_vector_text(path);
    for(int i=0; i<array.size(); i++)
    {
        cout<<"printing "<< i+1 <<" element: "<<array[i]<<'\n';
    }

    return 0;
}