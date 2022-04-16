#include <iostream>
using namespace std;

int main()
{
    int myCase = 0;

    switch (myCase = 1)
    {
    case 1:
        cout << ++ myCase << endl;
        //break;
    
    default:
        cout << "ha" << endl;
        break;
    }

    return 0;
}