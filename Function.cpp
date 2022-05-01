#include<iostream>
using namespace std;

int main()
{
    int input = 0;
    int sum = 0;

// one can take text.txt file as input by execute .\exe < text.txt 
    while (cin >> input)
    {        
        sum += input;        
    }
    
    cout << sum << endl;

    return 0;
}
