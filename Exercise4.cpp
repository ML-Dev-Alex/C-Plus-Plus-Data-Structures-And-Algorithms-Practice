// Given an array of integers where each value is 1 <= x <= len(array),
// write a function that finds and prints all the duplicates in the array.
#include <iostream>
#include <cstdio>
using namespace std;
int arr1[] = {1, 2, 3};    // []
int arr2[] = {1, 2, 2};    // [2]
int arr3[] = {3, 3, 3};    // [3, 3]
int arr4[] = {2, 1, 2, 1}; // [1, 2]


// Solutions with O(n^2) or O(n log n) time complexity are trivial, we are going to use encoding 
// for a solution with O(n) time complexity and in place O(1) space complexity:
// Since we know all numbers in the arrays are between 1 and the length of the array,
// we can create relationships between the values and the indecies of the arrays,  
int dupes(int arr[], int n){
    cout << "[";
    for (int i = 0; i < n; i++){
        if (arr[ abs(arr[i]) - 1 ] < 0){
            cout << abs( arr[ abs(arr[i]) - 1] ) << ",";
        } else{
            // we use the value -1 to create an encoding with an index 
            // and set that index to negative. Now that index not only holds the normal value it used to have 
            // (if we take its absolute value before using it), but it also holds a binary information on wheter or not
            // we have already encountered such a value in the array
            arr[ abs(arr[i]) - 1 ] = -arr[ abs(arr[i]) - 1 ];
        }
    }
    cout << "]" << endl;
}


int main(){
    freopen( "Exercise4Output.txt", "w", stdout);  // log output
    dupes(arr1, sizeof(arr1) / sizeof(arr1[0]));
    dupes(arr2, sizeof(arr2) / sizeof(arr2[0]));
    dupes(arr3, sizeof(arr3) / sizeof(arr3[0]));
    dupes(arr4, sizeof(arr4) / sizeof(arr4[0]));

    return 0;
}