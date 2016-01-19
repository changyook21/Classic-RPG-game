#include <iostream>

using namespace std;

#include "item.h"
#include "backpack.h"

Backpack::Backpack() {
    initBackpack();
}

void Backpack::initBackpack() {
    stack = new DLLContainer<Item *>();
}

Backpack::Backpack(Backpack &other) {
    //stack = new DLLContainer<Item *>(*other.stack); //????????????????????????????????????????????
}

Backpack::~Backpack() {
    deleteBackpack();
}

void Backpack::deleteBackpack() {
    if (stack != NULL) {
        delete stack;
        stack = NULL;
    }
}

void Backpack::print() const {
    stack->resetIterator();
    
    cout << "[ ";
    while (stack->hasMore()) {
        Item *curItem = stack->next();
        cout << "(";
        curItem->print();
        cout << ") ";
    }
    cout << "]";
}

void Backpack::add(Item * item) {
    stack->pushBack(item);
}

bool Backpack::isEmpty() const {
    return stack->isEmpty();
}

int Backpack::size() const {  // int getNumItems()
    return stack->size();
}

int Backpack::capacity() const {
    return stack->size();
}

Item *Backpack::removeItemAt(int indexToRemove) {
    return stack->removeElementAt(indexToRemove);
}

Item *Backpack::getItemAt(int indexToReturn) {
    return stack->getElementAt(indexToReturn);
}

// Iterator
bool Backpack::hasMore() {
    return stack->hasMore();
}

Item *Backpack::next() {
    return stack->next();
}

void Backpack::resetIterator() {
    return stack->resetIterator();
}

//???????????????????????????????????????????????????????????????????????????????????????????????????
void Backpack::save(ostream &out) const {
    out << "#-------------------- class Backpack" << endl;

    out << "# numItems" << endl;
    out << stack->size() << endl;
  
    stack->resetIterator();

    out << "#======================================== slots[] begin" << endl;
    int i = 0;
    while (stack->hasMore()) {
        Item *curItem = stack->next();
        out << "#======================================== stack[" << i << "]" << endl;
        out << "# Item ID" << endl;
        out << curItem->getID() << endl;
        curItem->save(out);
        
        i++;
    }
    out << "#======================================== stack[] end" << endl;
}

//???????????????????????????????????????????????????????????????????????????????????????????????????
void Backpack::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Backpack" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    deleteBackpack();
    
    int numItems = 0; // must make one since we don't have one.
    //out << "# numItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numItems << endl;
    in >> numItems;
    in.get(); // skip enter code.

    initBackpack();
    
    //out << "#======================================== stack[] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    for (int i = 0; i < numItems; i++) {
        //out << "# slots[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << curItem->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        Item *itemToInsert = createItemByID(itemID); // call factory
        itemToInsert->load(in);
        add(itemToInsert);
    }
    //out << "#======================================== stack[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment   
}
