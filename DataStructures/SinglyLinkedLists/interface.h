#include <iostream>
#include <cstddef>
#include <assert.h>

struct Node {
    int data;
    Node *next;

    Node(int d){
        data = d;
        next = NULL;
    }
};

class LinkedList{
private:
    Node *start;
public:
    LinkedList(){
        start = NULL;
    }

    void insert_start(int data);
    void insert_place(int data, int place);
    void insert_end(int data);

    void delete_start();
    void delete_place(int place);
    void delete_end();

    void print_list();
};