#include <iostream>
#include <memory>
using namespace std;

struct node{
    shared_ptr<node> next;
    void* value;
};

// i. create_node()
shared_ptr<node> create_node(void* value){
    return make_shared<node>(node{nullptr, value});
}

// ii. push_front():
void push_front(shared_ptr<node>& head, void* value){
    auto new_node = create_node(value);
    new_node -> next = head;
    head = new_node;
}

// iii. push_back():
void push_back(shared_ptr<node>& head, void* value){
    auto new_node = create_node(value);
    
    if (!head) {
        head = new_node;
        return;
    }

    auto temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new_node;
}