#include <iostream>
#include <memory>
using namespace std;

struct nodo{
    shared_ptr<nodo> next;
    void* valor;
};

struct lista_enlazada{
    int size;
    shared_ptr<nodo> head;
};

shared_ptr<nodo> crear_nodo(void* valor){
    // nodo->next = NULL
    // nodo -> value = valor

}


