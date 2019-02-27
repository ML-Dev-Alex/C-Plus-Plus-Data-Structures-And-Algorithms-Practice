// An XOR linked list is a more memory efficient doubly linked list.
// Instead of each node holding next and prev fields, it holds a field named both,
// which is an XOR of the next node and the previous node. Implement an XOR linked list;
// it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.
#include <iostream>
#include <cstdio>
#include <inttypes.h>

using namespace std;

// Lets start by declaring the core node structure
struct Node{
    int value;
    int index;
    struct Node* both; // this is the XOR that points to previous and next node depending
    // on the direction we are currently "traveling"
}; 

// Find the XOR of node adresses
struct Node* XOR (struct Node *a, struct Node *b){
    return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

struct Node* add (struct Node **last, int value){
    struct Node *new_node = (struct Node*) malloc(sizeof (struct Node));
    new_node->value = value;
    new_node->both = XOR(*(last), NULL);  // New node always has an XOR between the last node on the list
    // and a NULL, as it is put at the end of the list.

    if (*last != NULL){
        new_node->index = (*last)->index + 1; // Increment the index 
        (*last)->both = XOR(new_node, (*last)->both); // change XOR pointer of previous node 
        // as it should also point to the new node now.
    }    
    else {
        new_node->index = 1; // start list if it is emtpy
    }
    return *last = new_node; // new node becomes the "last" on the list
}

struct NotOnList : public std::exception{
    const char *what() const throw()
    {
        return "Node not foud!";
    }
};

struct Node* get(int goalIndex, struct Node *startNode){
    struct Node *current = startNode;
    struct Node *previous = NULL;
    struct Node *next;

    // Navigate list, from either side, until we reach the end
    while (current != NULL) {
        if (current->index == goalIndex) {
            cout << "Node found! Index: " << current->index << ", " << "value: " << current->value << "." <<endl;
            return current;
        }
        next = XOR(previous, current->both); 

        previous = current;
        current = next;
    }

    throw(cout << "Not on list!", NotOnList());
}

void print(struct Node *startNode){
    struct Node *current = startNode;
    struct Node *previous = NULL;
    struct Node *next;

    if (startNode->index == 1) cout << "Starting from first node: "<< endl;
    else cout << "Starting from last node: "<< endl;

    // Navigate list, from either side, until we reach the end
    while (current != NULL){ 
        cout << "Index: " << current->index << " = " <<  current->value << endl;
        next = XOR(previous, current->both);

        previous = current;
        current = next;
    }
}

int main(int argc, char** argv){
    freopen( "Exercise2Output.txt", "w", stdout);  // log output

    // Populate list
    struct Node *last = NULL;
    struct Node *first = add(&last, 10);
    struct Node *second = add(&last, 20);
    struct Node *third = add(&last, 30);
    struct Node *fourth = add(&last, 40);

    print(first);
    print(last);
    cout << "Look for node 3:" << endl;
    struct Node *fund = get(3, first);
    cout << "Now look for node 9 (not on the list):" << endl;
    struct Node *notFound = get(9, first);
    
    return 0;
    
}