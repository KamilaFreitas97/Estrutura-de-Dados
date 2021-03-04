#ifndef MATRIZ_H
#define MATRIZ_H

#include <string>

struct Node;

class Matriz {
    private:
        int _l;
        int _c;
        Node *head;

        double busca(int i, int j);

    public:
        Matriz();
        Matriz(int l, int c);
        ~Matriz();
        void lerMatriz(std::string nome_do_arquivo);
        void imprime();
        void insere(int i, int j, double v);
        Matriz* soma(Matriz *B);
        Matriz* multiplica(Matriz *B);
};

#endif