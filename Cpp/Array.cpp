#include<iostream>
#include<climits>
#include<cmath>
#include<iomanip>

using namespace std;

int main()
{
    cout << INT_MIN << ", " << INT_MAX << endl;
        
    float myFloatArray[10] = {0.0};
    float f;
    int arraySize = sizeof(myFloatArray) / sizeof(myFloatArray[0]);
    cout << sizeof(myFloatArray) << ", " << sizeof(myFloatArray[0]) << endl;

    while (arraySize > 0)
    {
        f = sqrt(static_cast<float>(arraySize));
        cout << setprecision(10) << f << endl;
        myFloatArray[arraySize -1] = f;
        arraySize --;       
    }    
    
    cout << myFloatArray << endl;
    
    return 0;
}