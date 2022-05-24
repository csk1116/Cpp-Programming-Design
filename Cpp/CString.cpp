#include<iostream>
#include<iomanip>
#include<cctype> //for c ctype.h
#include<cstring> //for c string.h
#include<cstdlib> //string-number conversion
using namespace std;


void printableASCIITable();
void sortingNamesAlphabetically(char [][10], char*[], const int);
void swapName(char*, char*);
void swapPtr(char*&, char*&);

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
    //cin >> myCharArr; //seperate by white space
    cin.getline(myCharArr, 100); //input a string with white spaces.
    cout << myCharArr << endl;

    char* charptr = myCharArr;    
    //charptr = "abc"; //read only, and will cause memory leak.
    *(charptr + 2) = 'T';
    //charptr = strchr(myCharArr, 'a');   //pointer-based function
    cout << charptr << endl;
    
    const int CNT = 4;
    const int LEN = 10;
    
    char name[CNT][LEN] = {"JOHN", "MIKASA", "EREN", "ARMIN"}; 
    char nameP[CNT][LEN] = {"JOHN", "MIKASA", "EREN", "ARMIN"};      
    char* ptr[CNT] = {nameP[0], nameP[1], nameP[2], nameP[3]};   

    sortingNamesAlphabetically(name, ptr, CNT);      

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

    cout << "\n";
}

void sortingNamesAlphabetically(char nameArr[][10], char* ptrArr[], const int count)
{
   
    //print unsorted arr first.
    for(int i = 0; i < count; i++)
    {
        cout << nameArr[i] << " ";
    }
    cout << "\n";

    //implement by bubble sort
    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(strcmp(nameArr[j], nameArr[j+1]) > 0)
            {
                swapName(nameArr[j], nameArr[j+1]);
                swapPtr(ptrArr[j], ptrArr[j+1]);
            }
        }
    }


    //show sorted arr.
    for(int i = 0; i < count; i++)
    {
        cout << nameArr[i] << " " << ptrArr[i] << " ";        
    }
    cout << "\n";
}

void swapName(char* name1, char* name2)
{
    //swap by strcpy -> slow
    char temp[10] = {0};
    strcpy(temp, name1);
    strcpy(name1, name2);
    strcpy(name2, temp);    
}

void swapPtr(char*& name1, char*& name2) //call by ref at the char pointer
{
    //we can just swap pointer
    char* temp = nullptr;
    temp = name1;
    name1 = name2;
    name2 = temp;
}