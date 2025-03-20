#include <iostream>
#include <memory> // libreria para usar smart pointers
using namespace std;

struct node{
    shared_ptr<node> next;
    int value; 
};

// i. create_node()
shared_ptr<node> create_node(int value){
    return make_shared<node>(node{nullptr, value}); // uso make_shared<node>() para crear un nodo en memoria dinamica y devolver un shared_ptr
    // inicializo el nodo con node->next = nullptr y node->value = value
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
    
    if (!head) { // caso lista vacia
        head = new_node;
        return;
    }

    auto temp = head; // nodo auxiliar para recorrer la lista
    while (temp->next != NULL){ 
        temp = temp->next; // recorro toda la lista hasta llegar al ultimo nodo
    }
    temp->next = new_node;
}

// iv: insert():
void insert(shared_ptr<node>& head, int value, int position){
    auto new_node = create_node(value);

    if (position <= 1 || !head){ // si la posición es 1 (o un numero menor) o la lista está vacía, insertar al frente utilizando push_front()
        push_front(head, value); 
        return;
    }

    auto temp = head; // nodo auxiliar para recorrer la lista
    int count = 1; // contador para determinar cuantas posiciones estoy avanzando en la lista
    while (temp->next != NULL && count < position - 1){ // avanzar hasta la posición deseada
        temp = temp->next;
        count++;
    }

    if (temp->next == NULL && count < position - 1){ // caso: posicion es mas larga que la lista
        cout << "\nLa posicion " << position << " es mayor que el largo de la lista. Se va a insertar al final\n";
    }
    
    new_node->next = temp->next; // conecto el nuevo nodo con el siguiente nodo
    temp->next = new_node; // inserto el nuevo nodo en la posición correcta
}

// v. erase(): 
void erase(shared_ptr<node>& head, int position){
    if (head == NULL) return; // si la lista esta vacia, no hago nada

    if (position <= 1){ // caso: quiero eliminar la cabeza de la lista
        head = head->next;
        return;
    }

    // misma logica que en la funcion insert()
    auto temp = head;
    int count = 1;

    while (temp->next != NULL && temp->next->next != NULL && count < position - 1){
        temp = temp->next;
        count++;
    }

    if (head->next == NULL){ // caso: la posicion es mayor al tamaño de la lista
        cout << "\nLa posicion " << position << " es mayor que el largo de la lista. Se elimia el ultimo nodo\n";
        temp->next = nullptr; // elimino el ultimo nodo
        return;
    }

    temp->next = temp->next->next; 
}


// vi. print_list():
void print_list(shared_ptr<node>& head){
    auto temp = head;
    cout << "\n======= Lista Enlazada =======\n";
    
    if (!temp) {
        cout << "[Lista vacía]\n";
    } else {
        cout << "Inicio -> ";
        while (temp != nullptr) {
            cout << "[" << temp->value << "] -> ";
            temp = temp->next;
        }
        cout << "NULL";
    }

    cout << "\n=============================\n";
}

int main(){
    shared_ptr<node> head = nullptr; // inicializo la lista vacia
    
    // pruebo todas las funciones
    push_front(head, 5);
    insert(head, 12, 2);
    print_list(head); // esperado: 5 -> 12 -> NULL

    erase(head, 2);
    print_list(head); // esperado: 5 -> NULL

    push_back(head, 6);
    push_front(head, 1);
    insert(head, 3, 2);
    print_list(head); // esperado: 1 -> 3 -> 5 -> 6 -> NULL

    push_back(head, 20);
    push_back(head, 30);
    insert(head, 34, 76);
    push_back(head, 40);
    print_list(head); // esperado: 1 -> 3 -> 5 -> 6 -> 20 -> 30 -> 34 -> 40 -> NULL

    erase(head, 0);
    push_front(head, 2);
    print_list(head); // esperado: 2 -> 3 -> 5 -> 6 -> 20 -> 30 -> 34 -> 40 -> NULL

    insert(head, 1, -2);
    print_list(head); // esperado: 1 -> 2 -> 3 -> 5 -> 6 -> 20 -> 30 -> 34 -> 40 -> NULL


    erase(head, 100);
    print_list(head); // esperado: 1 -> 2 -> 3 -> 5 -> 6 -> 20 -> 30 -> 34 -> NULL

    erase(head, 5);
    erase(head, 7);
    erase(head, 4);
    erase(head, 2);
    erase(head, 6);
    erase(head, 1);
    erase(head, 3);
    print_list(head); // esperado: 3 -> NULL

    erase(head, 0);
    print_list(head); // esperado: [Lista vacía]

    return 0;
}