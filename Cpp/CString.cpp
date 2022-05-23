#include<iostream>
#include<iomanip>
#include<cctype> //for c ctype.h
#include<cstring> //for c string.h
#include<cstdlib> //string-number conversion
using namespace std;


void printableASCIITable();

int main()
{
    char myChar = 'A';    
    if(isupper(myChar))
    {
        cout << static_cast<char>(tolower(myChar)) << endl;
    }
    else
    {
        cout << myChar << endl;
    }    

    cout << isspace(myChar) << endl; //why not return bool ? because in c, there is no type: bool.

    printableASCIITable();

    char myCharArr[100] = {0};
    //cin >> myCharArr;
    cin.getline(myCharArr, 100); //input a string with white spaces.
    cout << myCharArr << endl;

    char* charptr = myCharArr;    
    //charptr = "abc"; //read only
    *(charptr + 2) = 'T';

    charptr = strchr(myCharArr, 'a');   //pointer-based function

    cout << charptr << endl;


    

    return 0;
}

void printableASCIITable()
{
    cout << "   0123456789\n";
    for(int i = 0; i <= 255; i++)
    {
        if(i % 10 == 0)
            cout << setw(2) << i / 10 << " ";
        if(isprint(i))
            cout << static_cast<char>(i);
        else
            cout << " ";
        if(i % 10 == 9)
            cout << "\n";
    }
}