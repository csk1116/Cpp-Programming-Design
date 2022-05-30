#include<iostream>
#include<string>
using namespace std;

int main()
{
    string myString = "my string ";
    string yourString = "your string";

    cout << myString.size() << endl;
    cout << yourString.length() << endl; 
    cout << myString.max_size() << endl;

    string ourString = myString + yourString;
    cout << ourString << endl;
    cout << ourString[5] << endl;
    cout << ourString.substr(1,3) << endl;

    string cinString; //cin.getline() >>  must be a C string
    getline(cin, cinString, '#'); //end with delimiter '#'
    cout << cinString << endl;
    
    string findString = "abcde";
    if(findString.find("bc", 0) != string::npos)    
        cout << findString.find("bc", 0) << endl;

    return 0;
}