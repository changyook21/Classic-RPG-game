#include <iostream>

using namespace std;

#include "main.h"
#include "item.h"
#include "unit.h"
#include "inventory.h"

Inventory::Inventory() {
    initSlots(INVENTORY_MAX_NUM_ITEM);
}

void Inventory::initSlots(int maxNumItems) {
    this->maxNumItems = maxNumItems;
    numItems = 0;
    slots = new Item *[maxNumItems];
    
    for (int i = 0; i < maxNumItems; i++) {
        slots[i] = NULL;
    }
    
    curIndexForIter = 0;
}

Inventory::~Inventory() {
    deleteSlots();
}

void Inventory::deleteSlots() {
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] != NULL) {
            delete slots[i];
        }
    }
    
    if (slots != NULL) {
        delete [] slots;
        slots = NULL;
    }
    
    numItems = 0;
    maxNumItems = 0;
    
    curIndexForIter = -1;
}

void Inventory::print() {
    cout << "[ ";
    for (int i = 0; i < maxNumItems; i++) {
        cout << "(";
        if (slots[i] != NULL) {
            slots[i]->print();
        }
        else {
            cout << " ";
        }
        cout << ") ";
    }
    cout << "]";
}

bool Inventory::add(Item *item) {
    if (numItems >= maxNumItems) {
        return false;
    }
    
    bool found = false;
    for (int i = 0; i < maxNumItems && !found; i++) {
        if (slots[i] == NULL) {
            slots[i] = item;
            numItems++;
            found = true;
        }
    }
    
    return true;
}

bool Inventory::insertItemAt(int index, Item *item) {
    if (index < 0 || index >= maxNumItems) {
        return false;
    }
    
    if (slots[index] != NULL) {
        return false;
    }
    
    if (item == NULL) {
        return false;
    }
    else {
        slots[index] = item;
        numItems++;
        return true;
    }
}

Item *Inventory::getItemAt(int index) {
    if (index < 0 || index >= maxNumItems) {
        return NULL;
    }
    
    return slots[index];
}

Item *Inventory::removeItemAt(int index) {
    if (index < 0 || index >= maxNumItems) {
        return NULL;
    }
    
    Item *itemToReturn = slots[index];
    if (itemToReturn != NULL) {
        numItems--;
    }
    
    slots[index] = NULL;
    
    return itemToReturn;
}

bool Inventory::isFull() {
    return numItems >= maxNumItems;
}

int Inventory::capacity() {
    return maxNumItems;
}

void Inventory::useItem(int index, Unit *unit) {
    if (slots[index] == NULL) {
        return;
    }
    
    if (slots[index]->use(unit)) {
        if (slots[index]->isMoved()) {
            slots[index] = NULL;
            numItems--;
        }
        else if (slots[index]->isDisposed()) {
            delete slots[index];
            slots[index] = NULL;
            numItems--;
        }
    }
}

bool Inventory::hasMore() {
    return curIndexForIter < maxNumItems;
}

// pre-condition: hasMore() == true
Item *Inventory::next() {
    return slots[curIndexForIter++];
}

void Inventory::resetIterator() {
    curIndexForIter = 0;
}

void Inventory::save(ostream &out) {
    out << "#-------------------- class Inventory" << endl;
    
    out << "# maxNumItems" << endl;
    out << maxNumItems << endl; 
    
    out << "# numItems" << endl;
    out << numItems << endl; 
    
    out << "#======================================== slots[] begin" << endl;
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] == NULL) {
            out << "#======================================== slots[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#======================================== slots[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            out << "# Item ID" << endl;
            out << slots[i]->getID() << endl;
            slots[i]->save(out);
        }
    }
    out << "#======================================== slots[] end" << endl;

}
 
void Inventory::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Inventory" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    deleteSlots(); // clear
    
    //out << "# maxNumItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumItems << endl;
    in >> maxNumItems;
    in.get(); // skip enter code.
    
    //out << "# numItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numItems << endl;
    in >> numItems;
    in.get(); // skip enter code.
    
    initSlots(maxNumItems); // build new array with the loaded maxNumItems
    //out << "#======================================== slots[] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    for (int i = 0; i < maxNumItems; i++) {
        //out << "# slots[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            slots[i] = NULL;
        }
        else {
            //out << "# Item ID" << endl;
            in.getline(buf, MAX_LEN_BUF); // skip comment
            //out << slots[i]->getID() << endl;
            string itemID = "";
            in >> itemID;
            in.get(); // skip enter code.
            
            slots[i] = createItemByID(itemID); // call factory
            slots[i]->load(in);
            numItems++;
        }
    }
    //out << "#======================================== slots[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //print();
}
