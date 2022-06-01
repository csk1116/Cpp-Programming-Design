#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class MyException: public logic_error
{
public:
    MyException(const string& msg = ""): logic_error(msg){}    
};

void throwAnExceptionByOurselves(int arr[], int len) throw(logic_error, MyException)
{
    int i = 0;
    cin >> i;
    if(i < 0 || i > len)
    {        
        throw logic_error("out of range!!");        
    }  
    else if(i == 2)
    {       
        throw MyException("my exception");        
    }
    arr[i] = 1;
}

void stringReplace(string& s, int i)
{  
    try
    {
        s.replace(i, 1, "-");
    }
    catch(out_of_range e) // <stdexcept>
    {
        cerr << e.what() << '\n';
    }    
}

int main()
{
    int arr[5] = {0};
    try
    {        
        throwAnExceptionByOurselves(arr, 5);    
    }
    catch(logic_error e)
    {
        cout << e.what() << endl;
    }
    catch(MyException e)
    {
        cout << e.what() << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    

    string myString = "hola";
    int i = 0;
    cin >> i;
    stringReplace(myString, i);
    cout << myString << endl;

    return 0;
}