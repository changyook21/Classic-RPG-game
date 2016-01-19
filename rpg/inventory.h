#ifndef INVENTORY_H
#define INVENTORY_H

class Item;
class Unit;

class Inventory {
protected:
    Item **slots;
    int maxNumItems;
    int numItems;
    
    // Iterator
    int curIndexForIter;
    
    // private helper functions
    void initSlots(int maxNumItems);
    void deleteSlots();
    
public:
    Inventory();
    virtual ~Inventory();
    
    void print();
    
    bool add(Item *item);
    bool insertItemAt(int index, Item *item);
    
    Item *getItemAt(int index);
    Item *removeItemAt(int index);
    
    bool isFull();
    int capacity();
    
    void useItem(int index, Unit *unit);
    
    // Iterator
    bool hasMore();
    Item *next();
    
    void resetIterator();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
