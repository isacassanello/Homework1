#include <iostream>
#include <memory>
using namespace std;

struct node{
    shared_ptr<node> next;
    int value;
};

// i. create_node()
shared_ptr<node> create_node(int value){
    return make_shared<node>(node{nullptr, value});
}

// ii. push_front():
void push_front(shared_ptr<node>& head, int value){
    auto new_node = create_node(value);
    new_node->next = head;
    head = new_node;
}

// iii. push_back():
void push_back(shared_ptr<node>& head, int value){
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

// iv: insert():
void insert(shared_ptr<node>& head, int value, int position){
    auto new_node = create_node(value);

    if (position <= 1 || !head){
        push_front(head, value);
        return;
    }

    auto temp = head;
    int count = 1;
    while (temp->next != NULL && count < position - 1){
        temp = temp->next;
        count++;
    }

    if (temp->next == NULL && count < position - 1){
        cout << "\nLa posicion " << position << " es mayor que el largo de la lista. Se va a insertar al final\n";
    }
    
    new_node->next = temp->next;
    temp->next = new_node;
}

// v. erase(): 
void erase(shared_ptr<node>& head, int position){
    if (head == NULL) return;

    if (position <= 1){
        head = head->next;
        return;
    }

    auto temp = head;
    int count = 1;

    while (temp->next != NULL && temp->next->next != NULL && count < position - 1){
        temp = temp->next;
        count++;
    }

    if (head->next->next == NULL){
        cout << "\nLa posicion " << position << " es mayor que el largo de la lista. Se elimia el ultimo nodo\n";
        temp->next = nullptr; 
        return;
    }

    temp->next = temp->next->next;
}


// vi. print_list():
void print_list(shared_ptr<node>& head){
    auto temp = head;
    cout << "------------------------------------------\n";
    while (temp != NULL){
        cout << temp->value << " -> ";
        temp = temp->next;
    }
    cout << "NULL \n";
    cout << "------------------------------------------\n";
}

int main(){
    shared_ptr<node> head = nullptr;
    
    push_front(head, 10);
    push_front(head, 5);
    push_front(head, 1);
    insert(head, 15, 3);
    print_list(head); // esperado: 1 -> 5 -> 15 -> 10 -> NULL

    push_back(head, 20);
    push_back(head, 30);
    push_back(head, 40);
    insert(head, 34, 76);
    print_list(head); // esperado: 1 -> 5 -> 15 -> 10 -> 20 -> 30 -> 40 -> 34 -> NULL

    erase(head, 1);
    print_list(head); // esperado: 5 -> 15 -> 10 -> 20 -> 30 -> 40 -> 34 -> NULL

    erase(head, 5);
    print_list(head); // esperado: 5 -> 15 -> 10 -> 20 -> 40 -> 34 -> NULL

    erase(head, 100);
    print_list(head); // esperado: 5 -> 15 -> 10 -> 20 -> 40 -> NULL

    return 0;
}