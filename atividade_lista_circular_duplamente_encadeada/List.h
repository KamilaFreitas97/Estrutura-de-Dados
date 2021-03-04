#ifndef LIST_H
#define LIST_H
#include <string>

struct Node;

class List
{
private:
   Node *head;

   Node *search(int x);

public:
   List();

   ~List();

   void push_back(int key);

   int pop_back();

   bool insertAfter(int key, int k);

   void remove(int key);

   void removeAll(int key);

   void print();

   void printReverse();

   bool empty();

   int size();

   void clear();

   void concat(List *lst);

   List *copy();

   void copyArray(int n, int arr[]);

   bool equal(List *lst);
};

#endif