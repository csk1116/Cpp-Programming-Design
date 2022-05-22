#include<iostream>
using namespace std;

void print(int**, int);
void print1D(int*, int);

int main()
{
    int len = 3;
    int** array = new int*[len];

    for(int i = 0; i < len; i++)
    {
        array[i] = new int[i + 1];
        for(int j = 0; j <= i; j++)
        {
            array[i][j] = j + 1;
        }
    }

    print(array, len);

    //****** delete ******!!!
    for(int i = 0; i < len; i++)
    {
        delete [] array[i];
        array[i] = nullptr;
    }

    delete [] array;
    array = nullptr;

    return 0;
}

void print1D(int* arr, int clen)
{
    for(int i = 0; i < clen; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << "\n";
}

void print(int** arr, int rlen)
{
    for(int i = 0; i < rlen; i++)
    {
        print1D(arr[i], i + 1);
    }
}