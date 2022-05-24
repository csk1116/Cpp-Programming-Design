#include<iostream>
#include<ctime>
#include<cmath>
using namespace std;

//structure, typedef, union, enumination, class

struct Point
{
    int x;
    int y;
    double distToOrigin()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    double distToOriginDec();
};

typedef Point Vector;
typedef double Dollar; //it is convinient to change data type from typedef. No need to go through all the variable.
const float PI = 3.14; //same concept like this.

void reflect(Point& p)
{
    int temp = p.x;
    p.x = p.y;
    p.y = temp;
}

void understandMemAllocForStruct()
{
    Point a[3];
    cout << sizeof(Point) << " " << sizeof(a) << endl;
    cout << &a << endl;

    for(int i = 0; i < 3; i++)
    {
        cout << &a[i] << " " << &a[i].x << " " << &a[i].y << endl;
    }
   
    Point* b = new Point[3];
    b->x = 1;
    b->y = 2;
    (b + 1)->x = 3;
    (b + 2)->x = 4;

    int* c = nullptr;
    cout << sizeof(b) << " " << sizeof(c) << " " << b[0].x << " " << b[1].x << " " << b[2].x << endl;   

    delete [] b;
    b = nullptr;   
}

int main()
{    
    clock_t sTime = clock();

    //struct
    Point myPoint = {100, 200};   
    myPoint.x += 100;
    myPoint.y -= 100;
    reflect(myPoint);
    cout << myPoint.x << ", " << myPoint.y << ", " << myPoint.distToOrigin() << endl; 
    understandMemAllocForStruct();

    //typedef
    Dollar nt = 0;
    Dollar us = 0;
    us = 50;
    nt = us * 30;
    cout << nt << endl;

    clock_t eTime = clock();   
    cout << static_cast<double>(eTime - sTime) / CLOCKS_PER_SEC << endl;

    return 0;
}

double Point::distToOriginDec() //scope resolution is required
{
    return sqrt(pow(x, 2) + pow(y, 2));
}


