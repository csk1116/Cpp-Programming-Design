#include<iostream>
using namespace std;

void swap1(int &, int &); //call by reference
void swap2(int, int); //call by value
void editArray(int [], int, int); //array is call by ref
int factorial(const int);

int main()
{
    int a = 10;
    int b = 20;
    int c[] = {1, 2, 3, 4, 5}; 

    swap1(a, b);
    cout << a << ", " << b << endl;

    swap2(a, b);    
    cout << a << ", " << b << endl;

    editArray(c, 5, 3);
    int arrayLength = sizeof(c)/sizeof(c[0]); 
    for(int i = 0; i< arrayLength; i++)
    {
        cout << c[i] << endl;
    }

    int f = a - b;
    cout << factorial(f) << endl;

    return 0;
}

void swap1(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

void swap2(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}

void editArray(int a[], int len, int add)
{
    for(int i = 0; i < len; i++)
    {
        a[i] += add;
    }
}

int factorial(const int n)
{
    //n = 20; protect n (read only)
    int ans = 1;
    for(int i = 1; i <=n; i++)
    {
        ans *= i;
    }
    return ans;
}
