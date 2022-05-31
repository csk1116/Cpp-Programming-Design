#include <iostream>
#include "myVector.h"
using namespace std;



int main()
{
    double i[2] = {-1.5, 2.5};
    MyVector2D vec1(i);
    vec1.printVector();
    cout << vec1[1] << endl;

    MyVector2D vec2(vec1);
    vec2[1] = 3.5;
    vec1.printVector();
    vec2.printVector();

    double j[2] = {-0.5, -0.5};
    NNVector2D vec3(j);    
    vec3.printVector();
    NNVector2D vec4(vec3);
    vec4.printVector();

    return 0;
}