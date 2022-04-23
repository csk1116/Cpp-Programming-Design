#include<iostream>
#include<climits>
#include<cmath>
#include<iomanip>

using namespace std;

int main()
{
    cout << INT_MIN << ", " << INT_MAX << endl;
    int a = 0;
    float f;
    int temp = INT_MAX;
    while (temp != 0)
    {
        f = sqrt((double)temp);
        cout << setprecision(10) << f << endl;
        temp /= 2;
        a++;
    }    
    
    cout << a << ", " << sizeof(int) << endl;
    return 0;
}