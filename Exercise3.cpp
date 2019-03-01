//Given an array of integers where every integer occurs three times except for one integer, which only occurs once, find and return the non-duplicated integer.
//
//For example, given [6, 1, 3, 3, 3, 6, 6], return 1. Given [13, 19, 13, 13], return 19.
//
//Do this in O(N) time and O(1) space.
#include <iostream>
#include <cstdio>
using namespace std;
int arr1[7] = {6, 1, 3, 3, 3, 6, 6};
int arr2[4] = {13, 19, 13, 13};


// Since all numbers appear a odd number of times most normal solutions are out of question
// The solution is going to be a bit tricky:
int findSingle(int arr[], int n){
    int odds = 0;
    int lastOdd = 0;
    int thirdOdd;
    for(int i = 0; i < n; i++){
        // Store the number that appears both in the odds variable (which stores numbers that appear a odd number of times)
        // and on the next element, or keep the previous "lastOdd" stored value if the current value stored on odd is 0
        lastOdd = lastOdd | (odds & arr[i]);
        
        // Store numbers that appear an odd number of times in the list
        // odds is either the value stored on an odd place or 0, depending of whether or not current value is equal to the 
        // last one or not
        odds = odds ^ arr[i];

        // Store a number if it appears for a third time, (for this to occur, the current odd number has to be equal to the last odd number)
        // which would mean that it is the third time we see it. 
        thirdOdd = ~(odds & lastOdd);

        // if thirdOdd is not 0, this means we found the last time a number has appeared in the array, and we can disregard it
        // (and remove it from odds and lastOdd) as it is not the number we were looking for.
        odds &= thirdOdd;
        lastOdd &= thirdOdd;
    }
    // The only number that remains should be the singleton
    return odds;
}



int main(){
    freopen( "Exercise3Output.txt", "w", stdout);  // log output
    cout << "First array ([6, 1, 3, 3, 3, 6, 6]) = " << findSingle(arr1, sizeof(arr1) / sizeof(arr1[0])) << endl;
    cout << "Second array ([13, 19, 13, 13]) = "  << findSingle(arr2, sizeof(arr2) / sizeof(arr2[0])) << endl;
    return 0;
}