# Day 15 - Classes and Tensor Skeleton

## Self notes

- structs are public members hence there is no private members. 
- Think of it like structs are public gyms while classes are private gyms with a few public accessible equipments. 
- Members of a class are private by default.

## What is a class in C++?

class is a user defiend container/template for creating objects

## What is the difference between public and private members?

public members can be accessed from any place but private can be accessed by that class only

## What is a constructor, and when is it called?

A constrcutor is a special member function that is automatically called when an obejct of a class is created

## What is a getter, and why are rows() and cols() getters?

A getter is a public member function that returns information from a private member without exposing the private member directly.

## What does encapsulation mean, and why do we keep rows_, cols_, and data_ private?

Encapsualtion is the practise of building data and methods that operate on that data into a single unit while restricting direct access to some of the object's components

## Why should the Tensor constructor validate dimensions before creating its internal data storage?

The constructor should validate rows and columns before allocating tensor storage so an invalid Tensor cannot be created and a negative size is not passed to std::vector.





# Day 16 - 