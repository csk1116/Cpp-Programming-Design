#include<iostream>
using namespace std;

int main()
{
    int input = 0;
    int sum = 0;

    while (cin >> input)
    {        
        sum += input;        
    }
    
    cout << sum << endl;

    return 0;
}
