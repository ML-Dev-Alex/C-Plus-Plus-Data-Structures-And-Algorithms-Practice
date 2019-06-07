#include "interface.h"

using namespace std;

void LinkedList::insert_start(int data){
    Node *new_start = new Node(data);

    new_start->next = start;
    start = new_start;

    cout << "New Starting Node with data: " << data << " added." << endl;
    print_list(); 
}

void LinkedList::insert_place(int data, int place){
    Node *new_node = new Node(data);

    if(start == NULL){
        if(place == 0){
            start = new_node;
        } else{
            assert(start == NULL && place == 0);
        }
    } else{
        Node *temp = start;
        Node *previous = NULL;
        for(int i = 0; i < place; i++){
            assert(temp != NULL);

            previous = temp;
            temp = temp->next;
        }
        
        if(previous == NULL){
            start = new_node;
            start->next = temp;
        } else{
            new_node->next = previous->next;
            previous->next = new_node;
        }
    }

    cout << "New Node at place " << place << " with data: " << data << " added." << endl;
    print_list();
}

void LinkedList::insert_end(int data){
    Node *new_end = new Node(data);

    if(start == NULL){
        start = new_end;
    }else {
        Node *temp = start;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_end;    
    }

    cout << "New End Node with data: " << data << " added." << endl;
    print_list();
}

void LinkedList::delete_start(){
    assert(start != NULL);

    Node *temp = start;
    start = start->next;
    delete temp;

    cout << "Start deleted." << endl;
    print_list();
    
}

void LinkedList::delete_place(int place){
    assert(start != NULL);

    Node *temp = start;
    Node *previous = NULL;

    for(int i = 0; i < place; i++){
        assert(temp != NULL);
        previous = temp;
        temp = temp->next;
    }

    if(previous == NULL){
        start = temp->next;
    } else {
        previous->next = temp->next;
    }
    delete temp;

    cout << "Place " << place << " deleted." << endl;
    print_list();
}

void LinkedList::delete_end(){
    assert(start != NULL);

    Node *temp = start;
    Node *previous = NULL;
    while(temp->next != NULL){
        previous = temp;
        temp = temp->next;
    }

    if(previous == NULL){
        start = NULL;
    } else{
        previous->next = temp->next;
    }
    delete temp;

    cout << "End deleted." << endl;
    print_list();
    
}

void LinkedList::print_list(){
    for(int i = 0; i < 100; i++){
        cout << '-';
    }
    cout << endl;

    Node *temp = start;
    cout << "List\t";
    while (temp != NULL){
        cout << temp->data << '\t';
        temp = temp->next;
    }
    cout << endl;

    for(int i = 0; i < 100; i++){
        cout << '-';
    }
    cout << endl;
    
}

