#include <iostream>
#include "Matriz.h"

using namespace std;

int main() {

    Matriz *m1 = new Matriz();//A
    Matriz *m2 = new Matriz();//B

    m1->lerMatriz("A.txt");
    m1->imprime();
    m2->lerMatriz("B.txt");
    m2->imprime();

    Matriz *m3 = m1->soma(m2);//C
    if(m3 == nullptr){
        cout<<"impossivel somar" << endl;
    }else{
        m3->imprime();
    }

    m2->lerMatriz("B2.txt");
    m1->imprime();
    m2->imprime();
    
    
    m3 = m1->soma(m2);
    if(m3 == nullptr){
        cout<<"impossivel somar" << endl;
    }else{
        m3->imprime();
    }
    
    m3 = m1->multiplica(m2);
    if(m3 == nullptr){
        cout<<"impossivel multiplicar" << endl;
    }else{
        m3->imprime();
    }
   
    m3 = m2->multiplica(m2);
    if(m3 == nullptr){
        cout<<"impossivel multiplicar" << endl;
    }else{
        m1->imprime();
        m2->imprime();
        m3->imprime();
    }

     
    delete m1;
    delete m2;
    delete m3;

    return 0;
}
