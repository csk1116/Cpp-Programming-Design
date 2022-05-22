#include<iostream>
#include<Windows.h>
using namespace std;

/* 
dynamic memory allocation
*/

int main()
{
    
    int len = 0;
    cin >> len;

    int* dma = new int[len]; //dma
    int test[len]; //some compiler is fine with this declaration, but it is compiler dependent. prevent it!

    for(int i = 0; i < len; i++)
    {                
        dma[i] = i;
        test[i] = i;
    }

    cout << dma[1] << ". " << test[1] << endl;

    // test memory leak --> terminate called after throwing an instance of 'std::bad_alloc' what(): std::bad_alloc
    while(1)
    {
        if(GetKeyState('Q') & 0x8000)
            break;

        int* ptr = new int[100000]; 
        cout << "..." << endl;
        delete [] ptr;
        ptr = nullptr;
    }

    return 0;
}