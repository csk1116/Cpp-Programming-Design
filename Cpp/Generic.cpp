#include<iostream>
using namespace std;

template<typename T>
void myPrint(T t)
{
    cout << t << endl;
}

template<typename A, typename B>
void twoSum(A a, B b)
{
    cout << a + b << endl;
}

template<typename T>
class MyClass
{
public:
    T multiplyByTwo(T number);
};

template<typename T>
T MyClass<T>::multiplyByTwo(T number)
{
    return 2 * number;
}

int main()
{
    myPrint<double>(5.5);
    myPrint<char>('a');

    twoSum<int, double>(5, 0.5);

    MyClass<double> class1;
    cout << class1.multiplyByTwo(3.3) << endl;

    return 0;
}