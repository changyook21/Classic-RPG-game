#ifndef EventQueue_H
#define EventQueue_H

class Event;

class EVNode {
public:
    Event *elem;
    EVNode *next;
	EVNode *prev;
    
    EVNode() {
        elem = NULL; 
        next = NULL;
		prev = NULL;
    }
    
    EVNode(Event *elem) {
        this->elem = elem;
        next = NULL;
		prev = NULL;
    }
};

class EventQueue {
private:
    EVNode *head;
    
    int numNodes; // size
    
    // Iterator
    EVNode *curIter;
    
public:
    EventQueue();
    virtual ~EventQueue();
    
	void print();

    bool enqueue(Event *elem);
    Event *dequeue();
    Event *peek();
    int size();
    
    // Iterator
    bool hasMore();
    Event *next();
    
    void resetIterator();
};

#endif