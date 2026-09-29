#include <iostream>

void increment_by_value(int number)
{
    ++number;
}

void increment_by_reference(int& number)
{
    ++number;
}

int main()
{
    int number {10};
    std::cout << "Original value: " << number << '\n';
    increment_by_value(number);
    std::cout << "After pass by value: " << number << '\n';
    increment_by_reference(number);
    std::cout << "After pass by reference: " << number << '\n';

    int* ptr{&number};
    std::cout<<"The integer value: "<<number<<'\n';
    std::cout<<"The integer's memory address: "<<&number<<'\n';
    std::cout<<"The address stored inside the pointer: "<<ptr<<'\n';
    std::cout<<"The value obtained by dereferencing the pointer: "<<*ptr<<'\n';
    int* ptr1{nullptr};
    if(ptr1)
    {
        std::cout<<"is not a nullpointer";
    }
    else
    {
        std::cout<<"is a nullpointer";
    }
    return 0;
}