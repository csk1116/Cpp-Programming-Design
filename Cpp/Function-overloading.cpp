#include<iostream>
using namespace std;

int test(int, int);
//double test(int, double);
//double test(double, int);
double test(double, double);
int test(int, int, int, int = 4); //default value

int main()
{
    cout << test(1, 2) << endl;
    cout << test(1.1123, 2.2234) << endl;
    cout << test(1, 2, 3) << endl;

    return 0;
}

int test(int a, int b)
{
    return a + b;
}

double test(double a, double b)
{
    return a + b;
}

inline int test(int a, int b, int c, int d) //not to use inline
{
    return a + b + c + d;
}