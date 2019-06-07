#include "interface.h"

using namespace std;

int main(){
    freopen( "singly_linked_list.txt", "w", stdout);  // log output
    LinkedList ll;

    for(int i = 0; i < 10; i++){
        if(i % 2){
            ll.insert_start(i);
        } else {
            ll.insert_end(i);
        }
    }

    ll.insert_place(7, 2);

    ll.delete_place(2);

    ll.delete_start();

    ll.delete_end();

    return 0;
}