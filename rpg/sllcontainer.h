#ifndef SLLCONTAINER_H
#define SLLCONTAINER_H

#include "main.h"

class SLLNode {
public:
    Tile *elem;
    SLLNode *next;
	SLLNode *prev;
    
    SLLNode() {
        elem = NULL; 
        next = NULL;
		prev = NULL;
    }
    
    SLLNode(Tile *elem) {
        this->elem = elem;
        next = NULL;
		prev = NULL;
    }
};

class SLLContainer {
private:
    SLLNode *head;
    
    int numNodes; // size
    
    // Iterator
    SLLNode *curIter;
    
public:
    SLLContainer();
    
    virtual ~SLLContainer();
    
	void print();

    int size();
    
    bool isEmpty();

	bool find(Tile *elem);
    
    bool insert(Tile *elem); // ordered용(pqueue등에서 사용)
                         // 만약 insert할때, prepend나, append를 섞어서 사용하지 말 것.
    
    Tile *removeGetMinFScoreTile();
    Tile *getMinHScoreTile();
    
    // Iterator
    bool hasMore();
    Tile *next();
    
    void resetIterator();
};

#endif