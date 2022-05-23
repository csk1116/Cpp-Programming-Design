#include<iostream>
using namespace std;

void printArr(int[], const int);
void insertionSortFromback(int [], const int); //recursion (pointer) 
void insertionSortFromfront(int [], const int); //recursion 

int main()
{
    int myArr1[10] = {3, 5, 1, 0, 9 ,200, 4, 90, 33, 4};
    int myArr2[10] = {5, 3, 9, 0, 1 ,200, 4, 4, 33, 90};
    const int length = sizeof(myArr1) / sizeof(myArr1[0]);
    
    cout << "arr1: " << endl;
    printArr(myArr1, length);
    insertionSortFromback(myArr1, length);
    printArr(myArr1, length);

    cout << "arr2: " << endl;
    printArr(myArr2, length);
    insertionSortFromfront(myArr2, length);
    printArr(myArr2, length);

    return 0;
}

void printArr(int arr[], const int len)
{
    for(int i = 0; i < len; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << "\n";
}



void insertionSortFromback(int arr[], const int len)
{
    if(len > 1)
    {
        insertionSortFromback(arr + 1, len -1);
        int first = arr[0];
        int compare = 1;
        for(; compare < len; compare++)
        {
            if(first > arr[compare])
            {
                arr[compare - 1] = arr[compare];
            }
            else
            {
                break;
            }
        }
        arr[compare - 1] = first;
    }
}

void insertionSortFromfront(int arr[], const int len)
{
    if(len <= 1)
    {
        return;
    }
    else
    {
        insertionSortFromfront(arr, len -1);

        int last = arr[len -1];
        int compare = len -2;

        while(compare >= 0 && arr[compare] >= last)
        {
            arr[compare + 1] = arr[compare];
            compare --;
        }
        arr[compare + 1] = last;
    }    
    
}