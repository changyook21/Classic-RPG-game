#ifndef BACKPACK_H
#define BACKPACK_H

#include "dllcontainer.h"
class Item;

class Backpack {
protected:
    DLLContainer<Item *> *stack;
    
    void initBackpack();
    void deleteBackpack();
public:
    Backpack();
    Backpack(Backpack &other);
    
    virtual ~Backpack();
    
    void print() const;
    
    void add(Item *item);
    
    bool isEmpty() const;
    int size() const; // int getNumItems();
    int capacity() const;
    
    Item *removeItemAt(int indexToRemove);
    Item *getItemAt(int indexToReturn);
    
    // Iterator
    bool hasMore();
    Item *next();
    
    void resetIterator();
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

#endif
