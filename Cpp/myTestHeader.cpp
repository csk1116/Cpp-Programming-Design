#include<iostream>
#include"myHeader.h"
using namespace std;

int main()
{
    myHeader();
    return 0;
}

// g++ a.cpp b.cpp ... -o c -I path(header)
// g++ myTestHeader.cpp myHeader.cpp -o myTestHeader -I C:/Users/CSK/git/Some-Basic-Practice/Header