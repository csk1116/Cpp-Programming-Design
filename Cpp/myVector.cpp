#include <iostream>
#include <iomanip>
#include "myVector.h"
using namespace std;

//MyVector
MyVector::MyVector() : dimension(0), vectorPtr(nullptr) {}

MyVector::MyVector(int dimension, double elements []) : dimension(dimension)
{   
    vectorPtr = new double[this->dimension];
    for(int i = 0; i < this->dimension; i++)
    {
        vectorPtr[i] = elements[i];
    }
}

//copy constructor
MyVector::MyVector(const MyVector& myVec) : dimension(myVec.dimension)
{   
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

//MyVector2D
//create the parent before creating the child
//if not specified, the parent's default constructor will be invoked.
MyVector2D::MyVector2D()
{
    this->dimension = 2;
    //this->vectorPtr = nullptr; is redundant
}
MyVector2D::MyVector2D(double elements[]) : MyVector(2, elements) {} 

//the parent's copy constructor will be automatically invoked.
//

void MyVector2D::printVector() const
{
    cout << "2D: "; 
    MyVector::printVector();
}

void MyVector2D::setValue(double e1, double e2)
{
    if(this->vectorPtr == nullptr)
        this->vectorPtr = new double[2];
    this->vectorPtr[0] = e1;
    this->vectorPtr[1] = e2;
}

//NNVector2D
NNVector2D::NNVector2D() {}

NNVector2D::NNVector2D(double elements[]) : MyVector2D(elements)
{
    this->vectorPtr[0] = elements[0] >= 0 ? elements[0] : 0;
    this->vectorPtr[1] = elements[1] >= 0 ? elements[1] : 0;
}

NNVector2D::NNVector2D(const NNVector2D& vec) : MyVector2D(vec)
{
    setValue(vec.vectorPtr[0], vec.vectorPtr[1]);
}

void NNVector2D::setValue(double e1, double e2)
{
    if(this->vectorPtr == nullptr)
        this->vectorPtr = new double[2];
    this->vectorPtr[0] = e1 >= 0 ? e1 : 0;
    this->vectorPtr[1] = e2 >= 0 ? e2 : 0;

}


