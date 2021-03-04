#include "Matriz.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

//construtor
Matriz::Matriz(int l, int c) {
    this->_l = l;
    this->_c = c;
    //alocando vetor
    this->_M = (float**)malloc(l * sizeof(float*));
    
    //criando vetor no _M
    for(int i = 0; i < l; i++) {
        this->_M[i] = (float*)malloc(c *sizeof(float));
        for(int j = 0; j < c; j++) {
            _M[i][j] = 0.0;
        }
    }
    
}
//destrutor
Matriz::~Matriz() {
    for(int i = 0; i < _l; i++) {
        free(_M[i]);
    }
    free(_M);
    cout <<"Matriz liberada"<< endl;
}

//retorna o numero de linhas
int Matriz::linhas() {
    return this->_l;
}
//retorna o numero de colunas
int Matriz::colunas() {
    return this->_c;
}

//imprime matriz
void Matriz::imprime(int largura){
    for(int i = 0; i < _l; i++) {
        for(int j = 0; j < _c; j++) {
            cout << setw(largura);
            cout << _M[i][j];
        }
        cout << endl;
    }
}

float Matriz::valor(int i, int j) {
    return this->_M[i][j];
}

void Matriz::atribui(float v, int i, int j) {
    this->_M[i][j] = v;
}

Matriz* Matriz::soma(Matriz *B) {
    if(B->_l != this->_l || B->_c != this->_c) {
        return nullptr;
    }

    Matriz *c = new Matriz(B->_l, B->_c);

    for(int i = 0; i < B->_l; i++) {
        for(int j = 0; j < B->_c; j++) {
            c->_M[i][j] = this->_M[i][j] + B->_M[i][j];
        }
    }

    return c;
}

Matriz* Matriz::multiplica(Matriz *B) {
    if(this->_c != B->_l) {
        return nullptr;
    }

    Matriz *c = new Matriz(this->_l, B->_c);

    for(int i = 0; i < _l; i++){
        for(int j = 0; j < B->_c; j++){
            for(int k = 0; k < _c; k++) {
                c->_M[i][j] += this->_M[i][k] * B->_M[k][j];
            }
        }
    }

    return c;
}