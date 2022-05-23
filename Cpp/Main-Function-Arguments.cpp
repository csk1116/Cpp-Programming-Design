#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl; //argv[0] is the name of executable file, argv[i] is the ith string passed into main.
    }
    return 0;
}