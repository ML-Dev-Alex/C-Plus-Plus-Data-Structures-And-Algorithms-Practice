// There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time.
// Given N, write a function that returns the number of unique ways you can climb the staircase. 
// The order of the steps matters.
// For example, if N is 4, then there are 5 unique ways:
// 1, 1, 1, 1
// 2, 1, 1
// 1, 2, 1
// 1, 1, 2
// 2, 2
#include <iostream>
#include <cstdio>
using namespace std;

// ladder size, number of ways, possible sets,
// Lets start by looking for patterns:
// n=1 = 1 = (1),
// n=2 = 2 = (1, 1), (2), 
// n=3 = 3 = (1, 2), (2, 1), (1, 1, 1),
// n=4 = 4 = (1, 1, 1, 1), (2, 1, 1), (1, 2, 1), (1, 1, 2), (2, 2)
// n=5 = 8 = (1, 1, 1, 1, 1), (2, 1, 1, 1), (1, 2, 1, 1), (1, 1, 2, 1), (1, 1, 1, 2), (2, 2, 1), (2, 1, 2), (1, 2, 2)
// n=6 = 13 = (1, 1, 1, 1, 1, 1), (2, 1, 1, 1, 1), (1, 2, 1, 1, 1), (1, 1, 2, 1, 1), (1, 1, 1, 2, 1), (1, 1, 1, 1, 2)
// (2, 2, 1, 1), (2, 1, 2, 1 ), (2, 1, 1, 2), (1, 2, 2, 1), (1, 2, 1, 2), (1, 1, 2, 2), (2, 2, 2), 

// this is exactly like the fibonacci sequence, where the answer for n is equal to the sum of the answers for n-1 and n-2
// Fib is very easy to compute with a recursive function:

int recursive(int n){
    if (n == 0 || n == 1) return 1;
    return recursive(n-1) + recursive(n-2);
}

// but this has O(n^2) as we have to compute two recursive calls for every call with n greater than 1
// If we store previous answers in an array we can reduce the time complexity to O(n)
// this is called memoization

int storage[9] = {0};
int recursive2(int n){
    if (storage[n] != 0) return storage[n];
    if (n == 0 || n == 1) return 1;
    return storage[n] = recursive2(n - 1) + recursive2(n - 2);
}

// We can still be more memory efficient, we don't need a full array with all the answers, we only need to lookup the last two
// and keep updating them.
int small[1] = {-1};
int recursive3(int n){
    if (small[0] <= 0 && small[1] <= 0){
        if (small[0] > small[1]) return small[0];
        else return small[1];
    }
    if (n == 0 || n == 1) return 1;
   
    if (small[1] < small[0]) return small[0] = recursive3(n - 1) + recursive3(n - 2);
    else return small[1] = recursive3(n - 1) + recursive3(n - 2);
}


int main(int argc, char** argv){
    freopen( "Exercise1Output.txt", "w", stdout);  // log output
    cout << "Result 1 = " << recursive(1) << endl;
    cout << "Result 2 = " << recursive(2) << endl;
    cout << "Result 3 = " << recursive(3) << endl;
    cout << "Result 4 = " << recursive(4) << endl;
    cout << "Result 5 = " << recursive(5) << endl;

    cout << "Faster Result 6 = " << recursive2(6) << endl;
    cout << "Faster Result 7 = " << recursive2(7) << endl;
    cout << "Faster Result 8 = " << recursive2(8) << endl;
    cout << "Faster Result 9 = " << recursive2(9) << endl;
    cout << "Faster Result 10 = " << recursive2(10) << endl;

    cout << "Smaller Space Result 11 = " << recursive3(11) << endl;
    cout << "Smaller Space Result 12 = " << recursive3(12) << endl;
    cout << "Smaller Space Result 13 = " << recursive3(13) << endl;
    cout << "Smaller Space Result 14 = " << recursive3(14) << endl;
    cout << "Smaller Space Result 15 = " << recursive3(15) << endl;
    return 0;
}

