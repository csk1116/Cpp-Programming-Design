#include <iostream>
using namespace std;

int main()
{
    int myCase = 0;

    cin >> myCase;
 
    switch (myCase)
    {
    case 1:
        cout << myCase -- << endl; 
    case 0:
        cout << myCase << endl;
        break;
    
    default:
        cout << "ha" << endl;
        break;
    }

    return 0;
}