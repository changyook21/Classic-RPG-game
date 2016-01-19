#ifndef DLLCONTAINER_H
#define DLLCONTAINER_H

#include "main.h"

template <class T>
class DLLNode {
public:
    T elem;
    DLLNode<T> *prev;
    DLLNode<T> *next;
    
    DLLNode() {
        elem = T();
        prev = NULL;
        next = NULL;
    }
    
    DLLNode(T elem) {
        this->elem = elem;
        prev = NULL;
        next = NULL;
    }
};

template <class T>
class DLLContainer {
private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    
    int numNodes; // size
    
    // Iterator
    DLLNode<T> *curIter;
    
public:
    DLLContainer();
    
    virtual ~DLLContainer();
    
    int size();
    
    bool isEmpty();
    
    T popBack();
    void pushBack(T elem);
    
    T dequeue();
    void enqueue(T elem);
    
    T getElementAt(int index);
    
    void prepend(T elem);
    void append(T elem);

    void insert(T elem); // ordered용(pqueue등에서 사용)
                         // 만약 insert할때, prepend나, append를 섞어서 사용하지 말 것.

    void insertElementAt(int index, T elem);
    
    T removeElementAt(int index);
    
    int indexOf(T elem);
    
    // Iterator
    bool hasMore();
    T next();
    
    void resetIterator();
};

#include "dllcontainer.cpp"

#endif