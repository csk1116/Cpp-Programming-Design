#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random> // try
using namespace std;

int main()
{
    cout << time(nullptr) << endl;

    srand(time(nullptr)); //assign the seed.

    for(int i = 0; i < 10; i++)
    {        
        cout << static_cast<double>(rand() % 501) / 100 << endl;  // 0 ~ 5
    }

    return 0;
}