#include<iostream>
#include<iomanip>
#include<cstdlib>
using namespace std;

class MyVector
{
private:
    int dimension; 
    //const int dimension; 
    double* vectorPtr;

public:    
    MyVector();
    MyVector(int dim, double elements []);
    MyVector(const MyVector& myVec); //self defined copy constructor with deep copy
    ~MyVector();
    void printVector() const; //const instance function, (can be called by non-const object, but cannot modify instance variable).
    bool isEqual(const MyVector& vec); //non-cont function cannot be called by const object, even if no instance variable is modified.
    bool operator==(const MyVector& vec) const; //operator overloading "operator+op" -> the number of parameters is restricted while type of param and return type is not
    bool operator<(const MyVector& vec) const;
    bool operator!=(const MyVector& vec) const;
    double operator[](int index) const;
    double& operator[](int index);
    void operator=(const MyVector& vec);//overloading assignment operator with deep copy (default is shallow copy)
};

MyVector::MyVector() : dimension(0), vectorPtr(nullptr) //member initializers, can initialize instance variable(especially for const instance variable)
{
    //dimension = 0;
    //vectorPtr = nullptr;
}

MyVector::MyVector(int dimension, double elements []) : dimension(dimension)
{
    //inside instance function, "this"(c++ key word) is a pointer storing the address of that object.
    //this->dimension <=> (*this).dimension = dimension
    //"this" can be used to distinguish object's variable and function's local variable with same name.
    //or other programmer would be clear that it is a instance variable.

    //this->dimension = dimension;
    vectorPtr = new double[this->dimension];
    for(int i = 0; i < this->dimension; i++)
    {
        vectorPtr[i] = elements[i];
    }
}

//copy constructor
MyVector::MyVector(const MyVector& myVec) : dimension(myVec.dimension)
{
    //dimension = myVec.dimension;
    vectorPtr = new double[dimension];
    for(int i = 0; i < dimension; i++)
    {
        vectorPtr[i] = myVec.vectorPtr[i];
    }
}

MyVector::~MyVector()
{
    delete [] vectorPtr;
}

void MyVector::printVector() const
{
    if(vectorPtr == nullptr)
    {
        cout << "empty vector!" << endl;
        return;
    }    
        
    cout << setprecision(3) << "(";
    for(int i = 0; i < dimension; i++)
    {
        if(i == dimension -1)
            cout << vectorPtr[i] << ")";
        else
            cout << vectorPtr[i] << ", ";                
    }
    cout << "\n";
}

bool MyVector::isEqual(const MyVector& vec)
{
    if(this->dimension != vec.dimension)
        return false;
    else
    {
        for(int i = 0; i < dimension; i++)
        {
            if(this->vectorPtr[i] != vec.vectorPtr[i])
                return false;
        }
    }
    return true;
}

//operator overloading
bool MyVector::operator==(const MyVector& vec) const
{
    if(this->dimension != vec.dimension)
        return false;
    else
    {
        for(int i = 0; i < dimension; i++)
        {
            if(this->vectorPtr[i] != vec.vectorPtr[i])
                return false;
        }
    }
    return true;
}

bool MyVector::operator<(const MyVector& vec) const
{
    if(this->dimension != vec.dimension)
        return false;
    else
    {
        for(int i = 0; i < dimension; i++)
        {
            if(this->vectorPtr[i] >= vec.vectorPtr[i])
                return false;
        }
    }
    return true;
}

bool MyVector::operator!=(const MyVector& vec) const
{
    return !(*this == vec);
}

double MyVector::operator[](int index) const
{
    if(index < 0 || index >= dimension)
        exit(1); //terminate the program by sending 1. But is not appropriate

    return vectorPtr[index];
}

//same implementation
double& MyVector::operator[](int index)
{
    if(index < 0 || index >= dimension)
        exit(1); 

    return vectorPtr[index];
}

void MyVector::operator=(const MyVector& vec)
{
    if(this == &vec && !(*this != vec))
    {
        cout << "same assignment!" << endl;
        return;
    }        

    if(this->dimension != vec.dimension)
    {       
        delete [] this->vectorPtr;
        this->dimension = vec.dimension;
        this->vectorPtr = new double[this->dimension];
    }
    for(int i = 0; i < dimension; i++)
    {
        this->vectorPtr[i] = vec.vectorPtr[i];
    }
}

int main()
{
    int vec1Dim = 5;
    double vec1Arr[5] = {1.111, 3.333, 5.555, 7.777, 9.999};
    MyVector vec1(vec1Dim, vec1Arr);
    MyVector vec2(vec1); //MyVector vec2 = vec1 --> compiler has default overloading assignment operator which does shallow copy.
    double originArr[5] = {0.0};
    const MyVector origin5D(vec1Dim, originArr);
    vec1.printVector();
    vec2.printVector();   
    origin5D.printVector();
    cout << (vec1.isEqual(vec2) ? "Y" : "N") << endl;
    cout << (origin5D == vec2 ? "Y" : "N") << endl;
    cout << (origin5D != vec2 ? "Y" : "N") << endl;
    cout << (origin5D.operator==(vec2) ? "Y" : "N") << endl;
    cout << (origin5D < vec2 ? "Y" : "N") << endl;
    vec1[2] = 100.10; 
    cout << vec1[2] << endl; //call the non-const one.
    cout << origin5D[3] << endl; //call the const one.

    vec2 = vec1;
    vec1.printVector();
    vec2[2] = 500.0;
    vec2.printVector();
    vec1 = vec1;

    return 0;
}