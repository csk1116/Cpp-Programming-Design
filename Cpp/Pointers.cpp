#include<iostream>
using namespace std;

void printAll(int, int, int, int);
//call by value
void swapV(int, int);
//call by ref
void swapR(int&, int&);
//call by pointer
void swapP(int*, int*);

int main()
{
    int a = 5;    
    int c = 9;
    int* ptr1 = &a;
    int* ptr2 = &c;

    //b is reference of a
    int& b = a;
    int d = b;

    printAll(a, b, c, d);
    cout << "value of ptr1: " << ptr1 << endl;
    cout << "address of a: " << &a << endl;
    cout << "address of b: " << &b << endl;
    cout << "address of ptr1: " << &ptr1 << endl;
    cout << "value of variable pointed by ptr1: " << *ptr1 << endl;

    swapV(a, c);
    printAll(a, b, c, d);

    swapR(a, c);
    printAll(a, b, c, d);

    //swapP(ptr1, ptr2);
    swapP(&a, &c);
    printAll(a, b, c, d);
   
    int* ptrArray[100] = {nullptr};
    //int valueArr[100] = {0};

    for(int i = 0; i < 100; i++)
    {
        //valueArr[i] = i;
        //ptrArray[i] = &valueArr[i];
        //cout << i << " " << *ptrArray[i] << endl; //runtime error
    }

    return 0;
}

void swapV(int x, int y)
{
    cout << "\ncall by value" << endl;
    int temp = x;
    x = y;
    y = temp;
}

void swapR(int& x, int& y)
{
    cout << "\ncall by ref" << endl;
    int temp = x;
    x = y;
    y = temp;
}

void swapP(int* x, int* y)
{
    cout << "\ncall by pointer" << endl;
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printAll(int a, int b, int c, int d)
{
    cout << "value of a: " << a << endl;
    cout << "value of b: " << b << endl;
    cout << "value of c: " << c << endl;
    cout << "value of d: " << d << endl;
}
