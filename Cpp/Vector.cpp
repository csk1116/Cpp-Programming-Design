#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void printVector(vector<T> vec)
{    
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;

    vec[0] += 100; //copy constructor is deep copy
}

int main()
{
    vector<int> intVector;
    cout << intVector.size() << endl;
    cout << intVector.max_size() << endl;
    intVector.push_back(7);
    intVector.push_back(8);
    intVector.push_back(9);
    intVector.pop_back();
    printVector(intVector);
    cout << intVector[0];

    return 0;
}