#include <iostream>
#include <vector>

using namespace std;

vector<double> create_vector(int n)
{
    vector<double> array{};
    double temp;
    for(int iii=0; iii<n; iii++) // i was wrong here the condition was iii<=n but ii<n is the correct or it goes more than n
    {
        cout<<"Enter "<<iii<<" element: ";
        cin>>temp;
        array.push_back(temp);
    }
    return array;
}

double sum_vector(const vector<double>& array)
{
    if(array.empty())
    {
        cout<<"Vector is empty.";
        return 0;
    } 
    double sum{0};
    for(int iii=0; iii<array.size(); iii++)
    {
        sum+=array[iii];
    }
    return sum;
}

double max_abs(const vector<double>& array) //i first used vector<diuble> array instead of const vector<double>& array which was wrong. basically passing the whole array would result in lag and now using address instead of value as constant can make up what we were losing at first.
{
    if(array.empty())
    {
        cout<<"Vector is empty.";
        return 0;
    }
    double temp_abs;
    temp_abs=abs(array[0]);
    
    for(int i=1; i<array.size(); i++)
    {
        if(abs(array[i])>temp_abs)
        {
            temp_abs=abs(array[i]);
        }
    }

    return temp_abs;
}

int main()
{
    vector<double> array{};
    int n;
    cout<<"Enter the amount of values in the vector: ";
    if(n<=0)
    {
        cout<<"wrong input. bye bye.";
        return 1;
    }
    cin>>n;
    array=create_vector(n);
    cout<<"Sum of the elements of the vector is: "<<sum_vector(array)<<endl;
    cout<<"Maximum absolute of the elements of the vector is: "<<max_abs(array);
    return 0;
}