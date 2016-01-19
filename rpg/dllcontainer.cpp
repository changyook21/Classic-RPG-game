#include <iostream>

using namespace std;
template <class T>
DLLContainer<T>::DLLContainer() {
    head = NULL;
    tail = NULL;
    
    numNodes = 0;
    
    curIter = NULL;
}

template <class T>
DLLContainer<T>::~DLLContainer() {
    DLLNode<T> *current = head;
    
    while (current != NULL) {
        DLLNode<T> *nodeToDelete = current;
        
        current = current->next;
        delete nodeToDelete;
    }
    
    head = NULL;
    numNodes = 0;
    
    curIter = NULL;
}

template <class T>
int DLLContainer<T>::size() {
    return numNodes;
}

template <class T>
bool DLLContainer<T>::isEmpty() {
    return numNodes == 0;
}

// pre-condition: !isEmpty()
template <class T>
T DLLContainer<T>::popBack() {
    if (numNodes == 1) {
        T elemToReturn = tail->elem;
        delete tail;
        head = NULL;
        tail = NULL;
        numNodes--;
        return elemToReturn;
    }
    else {
        T elemToReturn = tail->elem;
        DLLNode<T> *newTail = tail->prev;
        newTail->next = NULL;
        delete tail;
        tail = newTail;
        numNodes--;
        return elemToReturn;
    }
}

template <class T>
void DLLContainer<T>::pushBack(T elem) {
    append(elem);
}

template <class T>
T DLLContainer<T>::dequeue() {
    if (numNodes == 1) {
        T elemToReturn = head->elem;
        delete head;
        head = NULL;
        tail = NULL;
        numNodes--;
        return elemToReturn;
    }
    else {
        T elemToReturn = head->elem;
        DLLNode<T> *newHead = head->next;
        newHead->prev = NULL;
        delete head;
        head = newHead;
        numNodes--;
        return elemToReturn;
    }
}

template <class T>
void DLLContainer<T>::enqueue(T elem) {
    append(elem);
}

// pre-condition: index >= 0 && index < size()
template <class T>
T DLLContainer<T>::getElementAt(int index) {
    if (index < 0 || index >= numNodes) {
        return T();
    }
    
    int curIndex = 0;
    DLLNode<T> *current = head;
    
    while (current != NULL && curIndex < index) {
        current = current->next;
        curIndex++;
    }
    
    return current->elem;
}

template <class T>
void DLLContainer<T>::prepend(T elem) {
    DLLNode<T> *newNode = new DLLNode<T>(elem);
    
    if (numNodes == 0) {
        head = newNode;
        tail = newNode;
        numNodes++;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        numNodes++;
    }
}

template <class T>
void DLLContainer<T>::append(T elem) {
    DLLNode<T> *newNode = new DLLNode<T>(elem);
    
    if (numNodes == 0) {
        head = newNode;
        tail = newNode;
        numNodes++;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        numNodes++;
    }
}

template <class T>
void DLLContainer<T>::insert(T elem) {
    DLLNode<T> *newNode = new DLLNode<T>(elem);
    
    if (numNodes == 0) {
        head = newNode;
        tail = newNode;
        numNodes++;
    }
    else if (numNodes == 1) {
        if (elem < head->elem) { // prepend
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            numNodes++;
        }
        else { // append
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            numNodes++;
        }
    }
    else {
        DLLNode<T> *prev = NULL;
        DLLNode<T> *current = head;
        
        while (current != NULL) {
            if (elem < current->elem) {
                break;
            }
            
            prev = current;
            current = current->next;
        }
        
        if (prev == NULL) { // prepend
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            numNodes++;
        }
        else if (current == NULL) { // append
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            numNodes++;
        }
        else { // insert between two nodes
            prev->next = newNode;
            newNode->prev = prev;
            current->prev = newNode;
            newNode->next = current;
            numNodes++;
        }
    }
}

// pre-condition: index >= 0 && index <= size()
template <class T>
void DLLContainer<T>::insertElementAt(int index, T elem) {
    if (index < 0 || index > numNodes) {
        return;
    }
    
    DLLNode<T> *newNode = new DLLNode<T>(elem);
    
    if (numNodes == 0) {
        head = newNode;
        tail = newNode;
        numNodes++;
    }
    else if (numNodes == 1) {
        if (index == 0) { // prepend
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            numNodes++;
        }
        else { // append
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            numNodes++;
        }
    }
    else {
        int curIndex = 0;
        DLLNode<T> *prev = NULL;
        DLLNode<T> *current = head;
        
        while (current != NULL && curIndex < index) {
            prev = current;
            current = current->next;
            curIndex++;
        }
        
        if (prev == NULL) { // prepend
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            numNodes++;
        }
        else if (current == NULL) { // append
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            numNodes++;
        }
        else { // insert between two nodes
            prev->next = newNode;
            newNode->prev = prev;
            current->prev = newNode;
            newNode->next = current;
            numNodes++;
        }
    }
}

// pre-condition: !isEmpty() && index >= 0 && index < size()
template <class T>
T DLLContainer<T>::removeElementAt(int index) {
    if (index < 0 || index > numNodes) {
        return T();
    }
    
    if (numNodes == 0) {
        return T();
    }
    else if (numNodes == 1) {
        T elemToReturn = head->elem;
        delete head;
        head = NULL;
        tail = NULL;
        numNodes--;
        return elemToReturn;
    }
    else {
        int curIndex = 0;
        DLLNode<T> *prev = NULL;
        DLLNode<T> *current = head;
        
        while (current != NULL && curIndex < index) {
            prev = current;
            current = current->next;
            curIndex++;
        }
        
        if (prev == NULL) { // delete head
            return dequeue();
        }
        else if (current != NULL && current->next == NULL) { // delete tail
            return popBack();
        }
        else { // remove the node between two nodes
            T elemToReturn = current->elem;
            prev->next = current->next;
            current->next->prev = prev;
            delete current;
            numNodes--;
            return elemToReturn;
        }
    }
}

template <class T>
int DLLContainer<T>::indexOf(T elem) {
    int indexFound = -1;
    
    int curIndex = 0;
    DLLNode<T> *current = head;
    
    while (current != NULL && indexFound == -1) {
        if (current->elem == elem) {
            indexFound = curIndex;
        }
        current = current->next;
        curIndex++;
    }
    
    return indexFound;
}

template <class T>
bool DLLContainer<T>::hasMore() {
    return curIter != NULL;
}

// pre-condition: hasMore() == true
template <class T>
T DLLContainer<T>::next() {
    T elemToReturn = curIter->elem;
    curIter = curIter->next;
    return elemToReturn;
}

template <class T>
void DLLContainer<T>::resetIterator() {
    curIter = head;
}