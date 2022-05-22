#include<iostream>
using namespace std;

int main()
{
    int a = 5;
    int* ptr1 = &a;

    cout << "value of a: " << a << endl;
    cout << "value of ptr1: " << ptr1 << endl;
    cout << "address of a: " << &a << endl;
    cout << "address of ptr1: " << &ptr1 << endl;
    cout << "value of variable pointed by ptr1: " << *ptr1 << endl;

    int* ptrArray[100] = {nullptr};

    for(int i = 0; i < 100; i++)
    {
        cout << i << " " << *ptrArray[i] << endl; //runtime error
    }

    return 0;
}