#include <iostream>
#include <string>
#include <climits>
#include "List.h"

struct Node {
    int value;
    Node *next;
    ~Node() { std::cout << "no com valor " << value << " liberado" << std::endl; }
};




List::List() {
    head = new Node;
    head->next = head; //cabeça
    head->value = 77777777;
}

// Completar



List::~List(){
    clear();
    delete head;
    std::cout<< "lista liberada" <<std::endl;
    
}


    // Operacao auxiliar: retorna o no anterior ao no com valor x; 
    // ou retorna nullptr caso nenhum no com valor x esteja presente 
    Node *List::search(int x){
        Node *novo = head;
        Node *novo2 = head;
        while(novo->next != head){
            novo2 = novo;
            novo = novo->next;
            if(novo->value == x ){
                return novo2;
                
            }
        }
        return nullptr;
        
    }
    // contains: retorna true se a lista contem um no com valor x;
    // retorna false caso contrario
    bool List::contains(int x){
        return (search(x) != nullptr);
    }

    // empty: retorna true se a lista estiver vazia;
    // retorna false caso contrario
    bool List::empty(){
        return head->next == head;
    } 

    // size: retorna a quantidade de elementos na lista
    int List::size(){
        int cont = 0;
        Node *novo = head;
        while(novo->next != head){
            cont++;
            novo = novo->next;
        }
        return cont;
    }

    // clear: deixa a lista vazia, sem elementos  
    void List::clear(){
        Node *novo = head;
        Node *novo2 = head;
        while(novo->next != head){
            novo2 = novo->next;
            novo->next = novo2->next;
            delete novo2;
            
        }
    }
    
    // add_back: insere um no com valor x ao final da lista
    void List::add_back(int x){
        Node *novo = head;
        while(novo->next != head){
            novo = novo->next;
        }
        Node *novo2 = new Node;
        novo2->value = x;
        novo->next = novo2;
        novo2->next = head;
        
        
    }
    
    // add_front: insere um no com valor x no inicio da lista
    void List::add_front(int x){
        Node *novo = new Node;
        novo->value = x;
        novo->next = head->next;
        head->next = novo;
    }
    
    // remove_front: remove o elemento que esta no inicio da lista
    // retorna o valor do no caso ele exista; 
    // ou retorna INT_MIN caso não exista primeiro elemento
    int List::remove_front(){
        if(empty()){
            return INT_MIN;
        }
        
        Node *novo = head->next;
        int v; //valor
        v = novo->value;
        head->next = novo->next;
        delete novo;
        return v;
        
    }

    // remove_back: remove o elemento que esta no final da lista 
    // retorna o valor do no caso ele exista; 
    // ou retorna INT_MIN caso não exista ultimo elemento
    int List::remove_back(){
        if(empty()){
            return INT_MIN;
        }
        Node *novo = head;
        Node *novo2 = head;
        while(novo->next != head){
            novo2 = novo;
            novo = novo->next;
        
        }
        novo2->next = head;
        int v;
        v = novo->value;
        delete novo;
        return v;
        
    }

    // remove: remove o primeiro no com valor x
    void List::remove(int x){
        Node *novo = search(x);
        if(novo != nullptr){
            Node *novo2 = novo->next;
            novo->next = novo2->next;
            delete novo2;
            
        }
    }

    // removeAll: remove todos os nos com valor x
    void List::removeAll(int x){
        Node *novo = search(x);
        while(novo != nullptr){
            Node *novo2 = novo->next;
            novo->next = novo2->next;
            delete novo2;
            novo = search(x);
        }
        
    }
    
    // toString: retorna a lista como uma std::string
    std::string List::toString(){
        std::string s = "[";
        Node *novo = head;
        
        while(novo->next != head){
            novo = novo->next;
            if(novo->next != head){
                s = s + std::to_string(novo->value) + ",";
            
            }else{
                s = s + std::to_string(novo->value);
            
            }
        }
        s = s + "]";
        
        return s;
        
    }
    
