// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

// Find the sum of all the multiples of 3 or 5 below 1000.
#include <iostream>
#include <cstdio>
using namespace std;


int example1 = 10;
int example2 = 1000;

int multiples(int n){
    int sum = 0;
    for (int i = 0; i < n; i++)
        if (i % 3 == 0 || i % 5 == 0) sum += i;
    
    return sum;
}

int main(){
    freopen( "Exercise6Output.txt", "w", stdout);  // log output
    cout << "Sum of multiples of 3 and 5 below 10: " << multiples(example1) << endl;
    cout << "Sum of multiples of 3 and 5 below 1000: " << multiples(example2) << endl;
    
    return 0;
}