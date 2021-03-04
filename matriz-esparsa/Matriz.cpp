//MARIA KAMILA DA SILVA FREITAS - 404334
//Jessica Maria Nunes da Silva - 392278

#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::setw;
//CRIANDO ESTRUTURA
//COMPLEXIDADE:
struct Node {
    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double value;

    Node(){}
    ~Node(){}
};

Matriz::Matriz() {}

// CONSTRUTOR QUE CRIA UMA MATRIZ COM AS LISTAS DE CABEÇAS PRONTAS PARA PODER INSERIR VALORES
//COMPLEXIDADE: O(L+C)
Matriz::Matriz(int l, int c) {   
    // ATRIBUINDO LINHAS E COLUNAS DA MATRIZ
    this->_l = l;//1
    this->_c = c;//1

    // INÍCIO: ALOCANDO AS CABEÇAS
    this->head = new Node();//1

    this->head->linha = -1;//1
    this->head->coluna = -1;//1
    this->head->direita = this->head;//1
    this->head->abaixo = this->head;//1

    Node *ultimo = this->head;//1

    // CRIANDO L NÓS CABEÇAS PARA A PRIMEIRA LINHA DE NÓS CABEÇAS
    for(int i = 0; i < l; i++) { //O (L)
        Node *head_linha = new Node();//1L
        //colocando 0 eu consigo comparar na hora de inserir e mostrar
        head_linha->linha = 0;//1L
        head_linha->coluna = -1;//1L
        head_linha->abaixo = head_linha;//1L

        ultimo->direita = head_linha;//1L
        head_linha->direita = this->head;//1L
        ultimo = head_linha;//1L // O ULTIMO AGORA É QUEM EU ACABEI DE INSERIR
    }

    ultimo = this->head;//1

    // CRIANDO C NÓS CABEÇAS PARA A PRIMEIRA COLUNA DE NÓS CABEÇAS
    for(int i = 0; i < c; i++) {//O(C)
        Node *head_coluna = new Node();

        head_coluna->linha = -1;//1C
        head_coluna->coluna = 0;//1C
        head_coluna->direita = head_coluna;//1C

        ultimo->abaixo = head_coluna;//1C
        head_coluna->abaixo = this->head;//1C
        ultimo = head_coluna;//1C
    }
    // FIM: ALOCANDO AS CABEÇAS

    /*
        ESTE CONSTRUTOR CONSTRÓI A ESTRUTA DE CABEÇAS NO FORMATO:

        x h h h h
        h
        h
        h
        h

        EXEMPLO COM MATRIZ 4x4 ONDE head representa a cabeça "x"
    */
}

//
//A IDEIA DO DESTRUTOR E PECORRER LINHA POR LINHA DELETANDO SEMPRE O PRIMEIRO ELEMENTO
//QUANDO DELETA O PRIMEIRO ELEMENTO, ATUALIZA O PROXIMO, PARA SER PROXIMO DO ELEMENTO QUE FOI DELETADO 
//E ALEM DISSO TAMBEM ATUALIZA O PRONTEIRO DEBAIXO DO ELEMENTO QUE ESTA ACIMA, DO ELELEMTO QUE ACABOU DE SER DELETADO
//COMPLEXIDADE: PIOR CASO O(L*C + L + C)
Matriz::~Matriz() {
    Node *head_coluna = head->abaixo;//1
    Node *head_linha = head->direita;//1
    //
    while(head_coluna != head) {//1L
        while(head_coluna->direita != head_coluna) {//1C
            while(head_coluna->direita != head_linha->abaixo) {//1L
                head_linha = head_linha->direita;//1L
            } // SAIO DESSE LAÇO COM O NÓ QUE QUERO DELETAR A DIREITA DE head_coluna E ABAIXO DE head_linha

            Node *del = head_coluna->direita;//1
            //alterando o ponteiro da direita e de cima
            head_coluna->direita = del->direita;
            head_linha->abaixo = del->abaixo;

            cout << "(" << del->linha << ", " << del->coluna << ") No com valor "
            << del->value << " deletado." << endl;

            delete del;
        }
        head_coluna = head_coluna->abaixo; // DESÇO UMA LINHA
        head_linha = head->direita; // APONTO PARA O PRIMEIRO ELEMENTO PRA RECOMEÇAR O PROCESSO
    }

    while(head->direita != head) {//1C
        Node *del = head->direita;
        head->direita = del->direita;
        delete del;
    }

    while(head->abaixo != head) {//1L
        Node *del = head->abaixo;
        head->abaixo = del->abaixo;
        delete del;
    }

    cout << endl;
    delete head;
}

//LERMATRIZ CRIA MATRIZ E LER O ARQUIVO
//COMPLEXIDADE: E A MESA DO CONSTRUTOR O(L+C)
void Matriz::lerMatriz(string nome_do_arquivo) {
    int l, c;

    ifstream file(nome_do_arquivo);

    file >> l >> c;

    Matriz *novaMatriz = new Matriz(l, c);

    // COPIANDO CONTEÚDO CRIADO
    // PRECISO COPIAR O CONTEÚDO POIS SÓ O CONSTRUTOR DE MATRIZ CRIA AS LISTAS DE CABEÇAS
    this->_l = novaMatriz->_l;
    this->_c = novaMatriz->_c;
    this->head = novaMatriz->head;

    // INSERINDO VALORES (LENDO O RESTO DO ARQUIVO)
    int l_, c_;
    double v;

    while(file >> l_ >> c_ >> v) {
        this->insere(l_, c_, v);
    }

    file.close();
}
//PECORRE AS LINHAS E AS COLUNAS BUSCANDO TODOS OS ELEMENTOS I E J
//COMPLEXIDADE: O(L * C * (L+ C))
void Matriz::imprime() {
    for(int i = 1; i <= _l; i++) {//1L
        for(int j = 1; j <= _c; j++) {//1C
            double valor = busca(i, j);//1 L + C
            cout << setw(7);//1C
            if(valor != 0.0) {
                cout << valor;
            } else {
                cout << "0";
            }
        }
        cout << endl;
    }
    cout << endl;
}

/* void Matriz::imprime() {
    Node *head_coluna = head->abaixo;

    while(head_coluna != head) {
        Node *node_linha_ant = head_coluna;
        Node *node_linha_prox = head_coluna->direita;

        // CASO LINHA VAZIA, PRINT c 0's
        if(node_linha_prox == node_linha_ant) {
            for(int i = 0; i < _c; i++) {
                cout << setw(7);
                cout << "0";
            }
        }

        // CASO LINHA NÃO VAZIA, PERCORRO A LINHA DE 2 EM 2 OLHANDO OS NÚMEROS DAS COLUNAS
        // SEI QUE NÓS FORAM PULADOS QUANDO O NÚMERO DA COLUNA DO PRÓXIMO MENOS O NÚMERO DA COLUNA
        // DO ANTERIOR MENOS 1 É MAIOR QUE 0
        while(node_linha_prox != head_coluna) {
            int num_c_prox = node_linha_prox->coluna;
            int num_c_ant = node_linha_ant->coluna;
            int qtd_0 = num_c_prox - num_c_ant - 1;

            if(qtd_0 > 0) {
                while(qtd_0--) {
                    cout << setw(7);
                    cout << "0";
                }
            }

            cout << setw(7);
            cout << node_linha_prox->value;

            node_linha_ant = node_linha_prox;
            node_linha_prox = node_linha_prox->direita;

            // SE EU CHEGAR NO FIM MAS AINDA TEM COLUNAS PARA PREENCHER DE 0
            // CASO: PRÓXIMO É O ÚLTIMO
            if(node_linha_prox == head_coluna) {
                int num_c_faltam = this->_c - node_linha_ant->coluna;
                while(num_c_faltam--) {
                    cout << setw(7);
                    cout << "0";
                }
            }
        }

        cout << endl;
        //
        head_coluna = head_coluna->abaixo;
    }
    cout << endl;
} */

//A IDEIA DE INSERIR E PEGAR 2 PONTEIROS PARA AS CABECAS DA LINHA E COLUNA 
//ENTAO IR PARA A DIREITA ENQUANTO A COLUNA DO NO QUE EU QUERO INSERIR FOR MAIOR QUE A COLUNA DO NO ATUAL
//E PARA BAIXO ENQUANTO A LINHA DO NO QUE EU QUERO INSERIR FOR MAIOR QUE A LINHA DO NO ATUAL
//QUANDO ISSO ACONTECER ESTOU NA POSICAO CERTA DE INSERIR, O NOVO NO E ATUALIZAR OS PONTEIROS.
//COMPLEXIDADE: PIOR CASO INSERIR UM ELEMENTO NA ULTIMA LINHA E NA ULTIMA COLUNA DE UMA MATRIZ CHEIA. O(L + C )
void Matriz::insere(int i, int j, double v) {
    Node *novo = new Node();
    novo->linha = i;
    novo->coluna = j;
    novo->value = v;

    Node *head_linha = head;
    Node *head_coluna = head;

    while(i--) { // INDO PARA A LINHA CERTA
        head_linha = head_linha->abaixo; //1L
    }

    while(j--) { // INDO PARA A COLUNA CERTA
        head_coluna = head_coluna->direita;//1C
    }

    // QUANDO CHEGO NA LINHA CERTA, DEVO IR PARA FRENTE ENQUANTO A COLUNA
    // DO NOVO NÓ FOR MAIOR QUE A COLUNA DO NÓ ATUAL
    while(head_linha->direita->coluna < novo->coluna) {//1C
        if(head_linha->direita->coluna == 0) {
            break;
        }
        head_linha = head_linha->direita;
    } // SAIO DESSE LAÇO COM head_linha->direita SENDO O NÓ QUE DEVE FICAR A DIREITA DE novo

    novo->direita = head_linha->direita;
    head_linha->direita = novo;

    // SIMETRICAMENTE PARA AS COLUNAS, DEVO IR PARA BAIXO ENQUANTO A LINHA
    // DO NOVO NÓ FOR MAIOR QUE A LINHA DO DÓ ATUAL
    while(head_coluna->abaixo->linha < novo->linha) {//1L
        if(head_coluna->abaixo->linha == 0) {
            break;
        }
        head_coluna = head_coluna->abaixo;
    } // SAIO DESSE LAÇO COM head_linha->abaixo SENDO O NÓ QUE DEVE FICAR ABAIXO de novo

    novo->abaixo = head_coluna->abaixo;
    head_coluna->abaixo = novo;
}

/* Matriz* Matriz::soma(Matriz *B) {
    if(this->_c != B->_c || this->_l != B->_l) {
        return nullptr;
    }

    // RECRIEI O CONSTRUTOR PARA PODER FAZER ISSO AQUI
    Matriz *C = new Matriz(this->_l, this->_c);

    // PEGANDO NÓS CABEÇA DAS DUAS PRIMEIRAS LINHAS
    Node *head_start_1 = head->abaixo;
    Node *head_start_2 = B->head->abaixo;

    while(head_start_1 != head) {
        // PEGANDO O PRIMEIRO NÓ DE CADA LINHA
        Node *start_l1 = head_start_1->direita;
        Node *start_l2 = head_start_2->direita;

        while(start_l1 != head_start_1 && start_l2 != head_start_2) {
            int c_A = start_l1->coluna;
            int c_B = start_l2->coluna;

            // SE AS COLUNAS FOREM IGUAIS, DEVO FAZER UMA SOMA
            if(c_A == c_B) {
                C->insere(start_l1->linha, start_l1->coluna, start_l1->value + start_l2->value);

                start_l1 = start_l1->direita;
                start_l2 = start_l2->direita;
            } else {
                if(c_A < c_B) { // DEVO INSERIR O NÓ COM MENOR VALOR PRIMEIRO E SEGUIR PRA FRENTE
                    C->insere(start_l1->linha, start_l1->coluna, start_l1->value);
                    start_l1 = start_l1->direita;
                }
                else if(c_B < c_A) {
                    C->insere(start_l2->linha, start_l2->coluna, start_l2->value);
                    start_l2 = start_l2->direita;
                }
            }
        }

        // CHECANDO PARA SABER SE UMA LINHA ACABOU MAS OUTRA NÃO

        // CASO LINHA 2 ACABOU MAS LINHA 1 NÃO
        while(start_l1 != head_start_1) {
            C->insere(start_l1->linha, start_l1->coluna, start_l1->value);
            start_l1 = start_l1->direita;
        }

        // CASO LINHA 1 ACABOU MAS LINHA 2 NÃO
        while(start_l2 != head_start_2) {
            C->insere(start_l2->linha, start_l2->coluna, start_l2->value);
            start_l2 = start_l2->direita;
        }

        // INDO PARA PRÓXIMA LINHA
        head_start_1 = head_start_1->abaixo;
        head_start_2 = head_start_2->abaixo;
    }

    return C;
} */


//VOU PARA BAIXO ATE ESTA NA LINHA CERTA E PARA DIREITA ATE ENCONTRAR A COLUNA CERTA, SE 
//AO IR PARA DIREITA VOLTAR PARA O COMECO QUER DIZER QUE O ELEMENTO NAO EXISTE
//SE NAO FOI ENCONTRADO O ELEMENTO E RETORNO O VALOR DELE.
//COMPLEXIDADE: O(L + C)
double Matriz::busca(int i, int j) {
    Node *head_coluna = head;

    while(i--) {//1L
        head_coluna = head_coluna->abaixo;
    }

    Node *start = head_coluna->direita;

    while(start != head_coluna && start->coluna < j) {//1C
        start = start->direita;
    }

    if(start->coluna == j) {
        return start->value;
    }

    return 0.0;
}

//NA SOMA PECORREMOS TODAS AS LINHAS DE TODAS AS COLUNAS BUSCANDO ELEMENTO POR ELEMENTO
//SOMANDO OS VALORES E INSERINDO NA MATRIZ RESULTANTE
//COMPLEXIDADE: O (L * C *(L + C))
Matriz* Matriz::soma(Matriz *B) {
    if(this->_c != B->_c || this->_l != B->_l) {//1
        return nullptr;
    }

    // RECRIEI O CONSTRUTOR PARA PODER FAZER ISSO AQUI
    Matriz *C = new Matriz(this->_l, this->_c);

    for(int i = 1; i <= _l; i++) {//1L
        for(int j = 1; j <= _c; j++) {//1C
            double valor = this->busca(i, j) + B->busca(i, j);//L+C
            if(valor != 0.0) {
                C->insere(i, j, valor);//L+C
            }
        }
    }

    return C;
}

//PECORREMOS A MATRIZ PEGANDO LINHA DA PRIMEIRA MATRIZ E A COLUNA DA SEGUNDA, MULTIPLIANDO ELEMENTO
//POR ELEMENTO DESSAS LINHAS E COLUNAS, INSERINDO O VALOR NA MATRIZ RESULTANTE.
//COMPLEXIDADE: O(L * C² + (L + C))
Matriz* Matriz::multiplica(Matriz *B) {
    if(this->_c != B->_l) {//1
        return nullptr;
    }
    //RECRIEI O CONSTRUTOR
    Matriz *C = new Matriz(this->_l, B->_c);

    for(int i = 1; i <= _l; i++){//1L
        for(int j = 1; j <= B->_c; j++){//1C
            double valor = 0.0;
            for(int k = 1; k <= _c; k++) {//1C
                valor += this->busca(i, k) * B->busca(k, j);//L+C
            }
            if(valor != 0.0) {
                C->insere(i, j, valor);//L+C
            }
        }
    }

    return C;
}

/* Matriz* Matriz::multiplica(Matriz *B) {
    if(this->_c != B->_l) {
        return nullptr;
    }

    Matriz *C = new Matriz(this->_l, B->_c);

    Node *head_start_1 = head->abaixo;
    Node *head_start_2 = B->head->direita;
    //linha
    while(head_start_1 != head) {
        //coluna
        while(head_start_2 != B->head) {
            Node *start_1 = head_start_1->direita;
            Node *start_2 = head_start_2->abaixo;
            int l_A = start_1->linha;
            int c_B = start_2->coluna;
            double valor = 0.0;
            while(start_2 != head_start_2 && start_1 != head_start_1) {
                int c_A = start_1->coluna;
                int l_B = start_2->linha;
                cout << "(" << start_1->linha << ", " << start_1->coluna << "): " << start_1->value << " <-> ";
                cout << "(" << start_2->linha << ", " << start_2->coluna << "): " << start_2->value << endl;

                if(c_A == l_B) {
                    valor += start_1->value * start_2->value;
                    start_1 = start_1->direita;
                    start_2 = start_2->abaixo;
                } else {
                    if(c_A > l_B) {
                        start_2 = start_2->abaixo;
                    }
                    if(c_A < l_B) {
                        start_1 = start_1->direita;
                    }
                }
            }
            if(valor != 0.0) {
                cout << valor << endl;
                C->insere(l_A, c_B, valor);
            }
            head_start_2 = head_start_2->direita;
        }
        head_start_1 = head_start_1->abaixo;
    }

    return C;
} */





