#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "prop.h"
#include "tile.h"

Tile::Tile() {
    initTile(-1, -1);
}

Tile::Tile(int row, int col) {
    initTile(row, col);
}

void Tile::initTile(int row, int col) {
    this->row = row;
    this->col = col;
    
    fx = FX_NONE;
	
    unit = NULL;
    throwableItem = NULL;
    item = NULL;
    prop = NULL;
}

Tile::~Tile() {
    destroyTile();
}

void Tile::destroyTile() {
    if (unit != NULL) {
        delete unit;
        unit = NULL;
    }
    if (throwableItem != NULL) {
        delete throwableItem;
        throwableItem = NULL;
    }
    if (item != NULL) {
        delete item;
        item = NULL;
    }
    if (prop != NULL) {
        delete prop;
        prop = NULL;
    }
}

void Tile::print() {
//    if (astarStep != FX_NONE) {
//        cout << astarStep;
//        return;
//    }
    
    if (fx != FX_NONE) {
        cout << fx;
    }
    else if (unit != NULL) {
        unit->print();
    }
    else if (throwableItem != NULL) {
        throwableItem->print();
    }
    else if (item != NULL) {
        item->print();
    }
    else if (prop != NULL) {
        prop->print();
    }
    else {
        cout << TILE_EMPTY;
    }
}

char Tile::getFx() {
    return fx;
}

void Tile::setFx(char fx) {
    this->fx = fx;
}

void Tile::clearFx() {
    fx = FX_NONE;
}

Unit *Tile::getUnit() {
    return unit;
}

void Tile::setUnit(Unit *unit) {
    this->unit = unit;
}

Item *Tile::getThrowableItem() {
    return throwableItem;
}

void Tile::setThrowableItem(Item *throwableItem) {
    this->throwableItem = throwableItem;
}

Item *Tile::getItem() {
    return item;
}

void Tile::setItem(Item *item) {
    this->item = item;
}

Prop *Tile::getProp() {
    return prop;
}

void Tile::setProp(Prop *prop) {
    this->prop = prop;
}

void Tile::save(ostream &out) {    
    out << "#-------------------- class Tile" << endl;

    out << "# row" << endl;
    out << row << endl; 
    
    out << "# col" << endl;
    out << col << endl;
    
    /*
    if (unit == NULL) {
        out << "#======================================== unit" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== unit" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Unit ID" << endl;
        out << unit->getID() << endl;
        unit->save(out);
    }
    */
    /*
    if (throwableItem == NULL) {
        out << "#======================================== throwableItem" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== throwableItem" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# throwableItem ID" << endl;
        out << throwableItem->getID() << endl;
        throwableItem->save(out);
    }
     */
    
    if (item == NULL) {
        out << "#======================================== item" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== item" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << item->getID() << endl;
        item->save(out);
    }
    
    if (prop == NULL) {
        out << "#======================================== prop" << endl;
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << "#======================================== prop" << endl;
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Prop ID" << endl;
        out << prop->getID() << endl;
        prop->save(out);
    }
}

void Tile::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    destroyTile();
    
    //out << "#-------------------- class Tile" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    initTile(-1, -1);
    
    //out << "# row" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << row << endl;
    in >> row;
    in.get(); // skip enter code.
    
    //out << "# col" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << col << endl;
    in >> col;
    in.get(); // skip enter code.

    /*
    //out << "#======================================== unit" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    string tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        unit = NULL;
    }
    else {
        //out << "# Unit ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << unit->getID() << endl;
        string unitID = "";
        in >> unitID;
        in.get(); // skip enter code.
        
        unit = createUnitByID(unitID); // call factory
        unit->load(in);
    }
     */
    
    /*
    //out << "#======================================== throwableItem" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    string tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        throwableItem = NULL;
    }
    else {
        //out << "# throwableItem ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << throwableItem->getID() << endl;
        string throwableItemID = "";
        in >> throwableItemID;
        in.get(); // skip enter code.
        
        throwableItem = createItemByID(throwableItemID); // call factory
        throwableItem->load(in);
    }
     */
    
    //out << "#======================================== item" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    string tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        item = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << item->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        item = createItemByID(itemID); // call factory
        item->load(in);
    }

    //out << "#======================================== prop" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        prop = NULL;
    }
    else {
        //out << "# Prop ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << prop->getID() << endl;
        string propID = "";
        in >> propID;
        in.get(); // skip enter code.
        
        prop = createPropByID(propID); // call factory
        prop->load(in);
    }
}

//==============================================================================
// AStar related
//==============================================================================
void Tile::clearAStar() {
    astarStep = FX_NONE;
    
    f = INF;
    h = 0;
    g = INF;
    cameFrom = NULL;
}
//==============================================================================
// AStar related: end
//==============================================================================
