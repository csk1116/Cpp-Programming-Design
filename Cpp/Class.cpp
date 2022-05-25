#include<iostream>
#include<string>
using namespace std;

class MyVector
{    
private:
    string vectorName;
    int dimension;
    int* vectorPtr; //when we use default copy constuctor, point or array will do shallow copy
    static string version; 
    static int objectCount;
    friend void testGlobalFriendFunc(); //friend of global func or class can access private member. 
    friend class B;
public:
    MyVector(); //constructor, if not defined, compiler will prvide a default constructor 
                //that dose nothing. destructor likewise. 
    MyVector(string name, int dim, int iniValue = 0); //constructor overloading with default iniValue 
    MyVector(const MyVector& vec); //overloading copy constructor
    ~MyVector(); //destructor    
    string getName() { return vectorName; } //getter
    void setName(string name) { vectorName = name; } //setter
    void reviseVec(int value);
    void printVector();
    static int getActiveObjectCount() { return MyVector::objectCount; }
    static string getVersion() { return MyVector::version; } //static funtion may access static member.
                                                //cannot access other instance member. 
    static void setVersion(string newVersion) { MyVector::version = newVersion; }
};

string MyVector::version = "1.0.0.0"; //default
int MyVector::objectCount = 0; //default

MyVector::MyVector()
{
    vectorName = "";
    dimension = 0;
    vectorPtr = nullptr;
    MyVector::objectCount ++;
    cout << "myVector constructed" << endl;
}
MyVector::MyVector(string name, int dim, int iniValue)
{
    vectorName = name;
    dimension = dim;
    vectorPtr = new int[dimension];
    for(int i = 0; i < dimension; i++)
    {
        vectorPtr[i] = iniValue;
    }
    MyVector::objectCount ++;
    cout << "myVector constructed" << endl;
}
MyVector::MyVector(const MyVector& vec)
{
    vectorName = vec.vectorName;
    dimension = vec.dimension;
    vectorPtr = new int[dimension];
    for(int i = 0; i < dimension; i++)
    {
        vectorPtr[i] = vec.vectorPtr[i];
    } 
    MyVector::objectCount ++;
    cout << "myVector deep copied" << endl;
}
MyVector::~MyVector()
{
    delete [] vectorPtr;
    cout << "myVector destructed" << endl;
    MyVector::objectCount --;
}
void MyVector::reviseVec(int val)
{
    for(int i = 0; i < dimension; i++)
    {
        vectorPtr[i] = val;
    }
}
void MyVector::printVector()
{
    if(vectorPtr == nullptr)
    {
        cout << "empty vector!" << endl;
        return;
    }
    else
    {
        cout << getName() << endl;
    }
        
    cout << "(";
    for(int i = 0; i < dimension; i++)
    {
        if(i == dimension -1)
            cout << vectorPtr[i] << ")";
        else
            cout << vectorPtr[i] << ", ";                
    }
    cout << "\n";
}

//Friend : global function
void testGlobalFriendFunc()
{
    MyVector vec("test", 4, 10);
    vec.printVector();
    cout << vec.dimension << endl;    
}

//Friend : class
//Timing for constructors/destructors
class A
{
private:
public:
    A() {cout << "startA\n";}
    ~A() {cout << "endA\n";}
};

class B
{
private:
    A myA;
public:
    B() {cout << "startB\n";}
    ~B() {cout << "endB\n";}
    void testClassFriendFuc(MyVector vec) //default copy constructor in MyVector looks like: Vector(const Vector& vec){ ... copy each member ...}, overloading the copy constructor to solve it.
    {
        cout << "pass by value" << endl;
        cout << vec.dimension << endl;
    }
    void testClassFriendFucPtr(const MyVector* vecptr)
    {
        cout << "pass by pointer" << endl; //don't have to copy the object(waste memory) but one can trade off on time.
        cout << vecptr->dimension << endl;
    }
    void testClassFriendFucRef(const MyVector& vec) //use const to prevent reference being modified.
    {
        cout << "pass by reference" << endl; //don't have to copy the object(waste memory) but one can trade off on time.
        cout << vec.dimension << endl;
    }
};


int main()
{
    MyVector vec1("vec1", 3,10301);
    MyVector vec2("vec2",5);
    vec2.setName("VEC2");
    MyVector vec3;
    MyVector vec4(vec2);
    vec4.setName("vec4");
    vec4.reviseVec(100); //because shallow copy, which will affect vec2.
    vec1.printVector();
    vec2.printVector();
    vec3.printVector();
    vec4.printVector();
    cout << "active objcet: " << MyVector::getActiveObjectCount() << endl;

    //object pointer
    MyVector* vecPtr = &vec1;
    vecPtr->printVector(); //is equivalent to (*vecPtr).printVector();

    //friends
    testGlobalFriendFunc();

    B myB;
    myB.testClassFriendFucPtr(vecPtr);
    myB.testClassFriendFucRef(vec1);

    //static
    cout << MyVector::getVersion() <<endl;
    MyVector::setVersion("1.0.0.1");
    cout << MyVector::getVersion() <<endl;

    cout << "active objcet: " << MyVector::getActiveObjectCount() << endl;

    //dynamic object arrays
    MyVector* ptrArray[5]; //instead of creating object array, use pointer array to delay
                            //the invocation of object constructor.
    for(int i = 0; i < 5; i++)
    {
        ptrArray[i] = new MyVector(("V" + to_string(i)), (i + 1)); 
    } 
    ptrArray[3]->printVector();

    for(int i = 0; i < 5; i++)
    {
        delete ptrArray[i];
    } 

    return 0;
}