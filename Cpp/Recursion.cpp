#include<iostream>
using namespace std;


double max(double [], int);
unsigned int factorials(int); 
void insertionSort(int [], int);

int main()
{
    int unsortedArr[6] = {1, 2, 1, 2, 100, 1};
    double test[6] = {10, 8, 7, 10000, 3, 9};   
    insertionSort(unsortedArr, 6);
    for(int i = 0; i < 6; i++)
    {
        cout << unsortedArr[i] << endl;
    }
    cout << max(test, sizeof(test)/sizeof(test[0])) << endl;
    cout << factorials(10) << endl;
    return 0;
}

double max(double arr[], int len)
{
    if(len == 1)
    {
        return arr[0];
    }
    else
    {
        double subMax = max(arr, len -1);
        if(subMax > arr[len-1])
        {
            return subMax;
        }
        else
        {
            return arr[len-1];
        }
    }
}

unsigned int factorials(int n)
{
    if(n == 1)
        return 1;
    return n * factorials(n-1);
}

void insertionSort(int arr[], int len)
{
    if(len <= 1)
    {
        return;
    }
    else
    {
        insertionSort(arr, len -1);

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