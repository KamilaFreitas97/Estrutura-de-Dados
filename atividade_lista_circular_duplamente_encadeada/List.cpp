//Maria Kamila da Silva Freitas - 404334 
//Jessica Maria Nunes da Silva - 392278

#include "List.h"
#include <iostream>
#include <climits>

using namespace std;

//CRIANDO A ESTRUTURA PARA CADA NO
struct Node
{
    int value;
    Node *prox;
    Node *ant;
    ~Node() { cout << "Node com valor " << value << " liberado" << endl; }
};

//CONSTRUTOR E NELE QUE SERA INICIALIZADO OS ATRIBUTOS
//VAI CRIAR UMA LISTA DUPLAMENTE ENCADEADA
//COMPLEXIDADE: O(1)
List::List()
{
    head = new Node;//1
    head->value = -777777;//1
    head->prox = head;//1
    head->ant = head;//1
}


//DESTRUTOR VAI LIBERAR TODA A MEMORIA QUE FOI ALOCADA NA LISTA
//COMPLEXIDADE: O(N)
List::~List()
{
    clear();//1N
    delete head;//1
    cout << "lista liberada" << endl;//1
}

//OPERACAO AUXILIAR ONDE
//SEARCH REALIZA A BUSCA PELO INTEIRO X DENTRO DA LISTA
//ENQUANTO O PROX ELEMENTO FOR DIFERENTE DO NO CABECA O NOVO VAI RECEBER O PROX VALOR DE X 
//SE O NOVO VALOR FOR IGUAL A X VAI RETORNAR O VALOR DO ANTERIOR DA LISTA CASO NAO RETORNA NULLPTR

//COMECA DA CABECA E PECORRE ELEMENTO POR ELEMENTO PROCURANDO UM NO COM VALOR IGUAL A X, SE ENCONTRAR RETORNA O 
//PONTEIRO PARA O ANTERIOR CASO NAO RETORNA NULLPTR
//COMPLEXIDADE: O(N)
Node *List::search(int x)
{
    Node *novo = head;//1
    while (novo->prox != head)
    {
        novo = novo->prox;//1N
        if (novo->value == x)//1N
        {
            return novo->ant;//1N
        }
    }
    return nullptr;
}//3*N + 1

//PUSH_BACK VAI INSERIR VALOR INTEIRO KEY NO FINAL DA LISTA
//COMPLEXIDADE:O(1)
void List::push_back(int key)
{
    Node *novo = head->ant;//1
    Node *novo2 = new Node;//1
    novo2->value = key; //1   //VAI ATUALIZAR O PROX DO ULTIMO
    novo->prox = novo2;//1
    novo2->prox = head;//1
    novo2->ant = novo;//1
    head->ant = novo2;//1
}

//POP_BACK VAI REMOVER O ELEMENTO QUE ESTA NO FINAL DA LISTA E RETORNAR O VALOR
//COMPLEXIDADE: O(1)
int List::pop_back()
{
    Node *novo = head->ant;//1
    int valor = novo->value;//1
    novo->ant->prox = novo->prox;//1
    novo->prox->ant = novo->ant;//1
    delete novo;//1
    return valor;//1
}

//INSERTAFTER VAI INSERIRI UM NOVO NO COM VALOR KEY APOS O K-ESIMO NO DA LISTA
//SE NAO TIVER POSICAO ELE NAO INSERIR

//COMECAMOS DA CABECA E VAMOS PARA FRENTE K VEZES OU ATE VOLTAR PARA O INICIO DA LISTA,
//SE VOLTAR PARA O INICIO DA LISTA, FICA EM LOOP E NAO EXISTE O K-ESIMO ELEMENTO E APENAS RETORNA A FUNCAO,
//SE NAO SAIMOS DO LACO COM NO NOVO NA POSICAO CERTA PARA SER INSERIDO O NO QUE FOR DESEJADO.
//COMPLEXIDADE: O(N), PIOR CASO SE INSERIR NO FINAL
void List::insertAfter(int key, int k)
{
    Node *novo = head;//1

    while (k > 0)
    { // SAÍ DO LAÇO COM NOVO NO K-ÉSIMO ELEMENTO
        k--;//1N
        novo = novo->prox;//1N
        if (novo == head)//1N
        { // CASO ENTRE EM CICLO, SUPONDO CASO TENTE INSERIR DEPOIS DE UMA POSIÇÃO INVÁLIDA
            return;
        }
    }

    Node *novo2 = new Node;//1
    novo2->value = key;//1

    novo2->prox = novo->prox;//1
    novo2->ant = novo;//1
    novo->prox = novo2;//1
    novo2->prox->ant = novo2;//1
}//3*N + 7


//REMOVE O PRIMEIRO NO COM VALOR KEY
//COMPLEXIDADE: O(N)
void List::remove(int key)
{
    Node *novo = search(key);//1
    if (novo != nullptr)
    {
        Node *novo2 = novo->prox;//1N
        novo->prox = novo2->prox;//1N
        novo2->prox->ant = novo;//1N
        delete novo2;//1N
    }
}//4 * N + 1

//REMOVEALL VAI REMOVER TODOS OS NOS COM VALORES KEY

//REMOVE TODOS OS ELELEMTOS QUE A FUNCAO SEARCH RETORNA
//COMPLEXIDADE: O(N)
void List::removeAll(int key)
{
    Node *novo = search(key);//1
    while (novo != nullptr)
    {
        Node *novo2 = novo->prox;//1N
        novo->prox = novo2->prox;//1N
        novo2->prox->ant = novo;//1N
        delete novo2;//1N
        novo = search(key);//1N
    }
}//5 * N + 1

//PRINT VAI IMPRIMIR TODOS OS ELEMENTOS QUE TA NA LISTA
//COMPLEXIDADE: O(N)
void List::print()
{
    Node *novo = head;//1
    while (novo->prox != head)
    {
        novo = novo->prox;//1N
        cout << novo->value << " ";//1
    }
    cout << endl;//1
}//2*N + 2

//PRINTREVERSE IMPRIME OS ELEMENTOS DA LISTA EM ORDEM REVERSA.

//PECORRE A LISTA AO CONTRARIO MOSTRANDO OS ELEMENTOS
//COMPLEXIDADE:
void List::printReverse()
{
    Node *novo = head;//1
    while (novo->ant != head)
    {
        novo = novo->ant;//1N
        cout << novo->value << " ";//1N
    }
    cout << endl;//1
}

//EMPTY VER SE A LISTA ESTA CHEIA OU VAZIA
//COMPLEXIDADE: O(1)
bool List::empty()
{
    return head->prox == head;//1
}

//SIZE RETORNA O NUMERO DE NOS DA LISTA

//PECORRE A LISTA SOMANDO +1 PARA CADA ELEMENTO
//COMPLEXIDADE: O(N)
int List::size()
{
    int cont = 0;//1
    Node *novo = head;//1
    while (novo->prox != head)
    {
        cont++;//1N
        novo = novo->prox;//1N
    }
    return cont;
}//2*N + 2

//CLEAR REMOVE TODOS OS ELEMENTOS DA LISTA E DEIXA APENAS OS NO CABECA

//PECORRE A LISTA DELETANDO ELEMENTO POR ELEMENTO
//COMPLEXIDADE: O(N)
void List::clear()
{

    Node *novo = head;//1
    Node *novo2 = head;//1
    while (novo->prox != head)
    {
        novo2 = novo->prox;//1N
        novo->prox = novo2->prox;//1N
        novo2->prox->ant = novo;//1N
        delete novo2;//1N
    }
}//4 * N + 2

//CONTACT VAI CONCATENA A LISTA ATUAL COM A LST PASSADA POR PARAMETRO 
//APOS ESSA OPERACAO SER EXECUTADA, LST SERA UMA LISTA VAZIA, SENDO ASSIM, O 
//UNICO NO DE LST SERA O NO CABECA

//NO CONCATENAR PRECISAMOS ATUALIZAR 3 PONTEIROS O ANTERIOR DO ULTIMO ELEMENTO DA PRIMEIRA LISTA,
//QUE PASSA A SER O PRIMEIRO ELEMENTO DA SEGUNDA LISTA, O ANTERIOR DO PRIMEIRO ELEMENTO DA SEGUNDA LISTA,
//PASSA A SER O ULTIMO ELEMENTO DA PRIMEIRA, E O PROXIMO DO ULTIMO ELEMENTO DA SEGUNDA LISTA, PASSA A SER A 
// CABECA DA PRIMEIRA LISTA. POR FIM ATUALIZAMOS A CABECA DA SEGUNDA LISTA PARA QUE OS PONTEIROS PROXIMO E ANTERIOR
//SEJAM A PROPRIA CABECA.
//COMPLEXIDADE: O(1)
void List::concat(List *lst)
{
    Node *novo = head->ant;//1
    Node *novo2 = lst->head->prox;//1
    Node *novo3 = lst->head->ant;//1

    novo->prox = novo2;//1
    novo2->ant = novo;//1

    novo3->prox = head;//1
    head->ant = novo3;//1

    lst->head->ant = lst->head;//1
    lst->head->prox = lst->head;//1
}

//COPY RETORNA UM PONTEIRO PARA UMA COPIA DA LISTA
//COMPLEXIDADE: O(N)
List *List::copy()
{
    Node *novo = head;//1
    List *l2 = new List;//1
    while (novo->prox != head)
    {
        novo = novo->prox;//1N
        l2->push_back(novo->value);//1N
    }
    return l2;//1
}//2 * N + 3

//COPYARRAY COPIA OS ELEMENTOS DO ARRAY ARR PARA A LISTA.
//O ARRAY ARR TEM N ELEMENTOS. TODOS OS ELEMENTOS ANTERIORES DA LISTA SAO MANTIDOS 
//E OS DO ARRAY ARR DEVEM SER ADICIONADOS APOS OS ELEMENTOS ORIGINAIS.
//COMPLEXIDADE: O(N)
void List::copyArray(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        push_back(arr[i]);//1N
    }
}

//EQUAL DETERMINA SE A LISTA PASSADA POR PARAMETRO E IGUAL A LISTA EM QUESTAO.
//DUAS LISTAS SAO IGUAIS SE ELAS POSSUEM O MESMO TAMANHO E O VALOR DO K-ESIMO ELEMENTO
//DA PRIMEIRA LISTA IGUAL E IGUAL AO K-ESIMO ELEMENTO DA SEGUNDA LISTA.

//PECORRE ELEMENTO POR ELEMENTO, VER SE OS VALORES SAO IGUAIS, SE ACHA ALGO DIFERENTE RETORNA FALSO
//CASO CONTRARIO  SAO IGUAIS
//COMPLEXIDADE: O(N)
bool List::equal(List *lst)
{
    if (size() != lst->size())
    {
        return false;
    }

    Node *novo = head;//1
    Node *novo2 = lst->head;//1
    while (novo->prox != head && novo2->prox != head)
    {
        if (novo->prox->value != novo2->prox->value)//1N
        {
            return false;
        }
        novo = novo->prox;//1N
        novo2 = novo2->prox;//1N
    }

    return true;
}//3*N + 2
