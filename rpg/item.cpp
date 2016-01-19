#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "board.h"
#include "event.h"
#include "eventqueue.h"

//extern Board *sim->board;
#include "sim.h"
extern Sim *sim;

//==============================================================================
//==============================================================================
//==============================================================================
// 1st Generation
//==============================================================================
//==============================================================================
//==============================================================================

//------------------------------------------------------------------------------
// class Item
//------------------------------------------------------------------------------
Item::Item() {
    this->shape = '\0';
    
    this->name = "";
    this->price = 0;

    disposed = false;
    moved = false;
    disposable = false;
    
    row = -1;
    col = -1;
}

Item::Item(const Item &other) {
    shape = other.shape;

    name = other.name;
    price = other.price;

    disposed = other.disposed;
    moved = other.moved;
    disposable = other.disposable;
    
    row = other.row;
    col = other.col;
}

Item::Item(char shape, string name, int price, bool disposable) {
    this->shape = shape;
    
    this->name = name;
    this->price = price;

    disposed = false;
    moved = false;
    this->disposable = disposable;

    row = -1;
    col = -1;
}

Item::~Item() {
}

void Item::print() const {
    cout << shape;
}

void Item::printFullSpec() const {
    cout << "(" << shape << ") " << setw(20) << left << name << right << " price(" << setw(6) << price << " g) ";
}

int Item::getRow() {
    return row;
}

void Item::setRow(int row) {
    this->row = row;
}

int Item::getCol() {
    return col;
}

void Item::setCol(int col) {
    this->col = col;
}

char Item::getShape() const {
    return shape;
}

int Item::getPrice() const {
    return price;
}

bool Item::isConsumable() const {
    return false;
}

bool Item::isEquippable() const {
    return false;
}

bool Item::isPotion() const {
	return false;
}

bool Item::isExpotion() const {
	return false;
}

bool Item::isArmor() const {
    return false;
}

bool Item::isWeapon() const {
    return false;
}

bool Item::isBounceshoe() const {
	// N/A
	return false;
}

bool Item::isBow() const {
	// N/A
	return false;
}
bool Item::isKey() const {
	// N/A
	return false;
}
bool Item::isTorch() const {
	// N/A
	return false;
}
bool Item::isBomb() const {
	// N/A
	return false;
}
bool Item::isDisposed() const {
    return disposed;
}

bool Item::isMoved() const {
    return moved;
}

void Item::dispose() {
    if (disposable) {
        disposed = true;
    }
}

//------------------------------------------------------------------------------
// only throwable items use functions below.
//------------------------------------------------------------------------------

bool Item::isVisited() const {
    return false;
}

void Item::resetVisited() {
}

void Item::fly() {
}

bool Item::isThrowableItem() const {
    return false;
}

bool Item::isArrow() const {
    return false;
}

void Item::effect(Unit *unit, Item *item, Prop *prop) {
    // N/A
}

//------------------------------------------------------------------------------
// only throwable items use functions above.
//------------------------------------------------------------------------------

void Item::save(ostream &out) const {
    out << "#-------------------- class Item" << endl;
    
    out << "# shape" << endl;
    out << shape << endl;
    out << "# name" << endl;
    out << name << endl;
    out << "# price" << endl;
    out << price << endl;
    out << "# disposed" << endl;
    out << disposed << endl;
    out << "# moved" << endl;
    out << moved << endl;
    out << "# row" << endl;
    out << row << endl;
    out << "# col" << endl;
    out << col << endl;
    //out << "# disposable" << endl;
    //out << disposable << endl;
    
    // skip
    // Board *board;
}

void Item::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Item" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# shape" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << shape << endl;
    in >> shape;
    in.get(); // skip enter code.
    
    //out << "# name" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << name << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    name = buf;
    //in.get(); // skip enter code.
    
    //out << "# price" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << price << endl;
    in >> price;
    in.get(); // skip enter code.
    
    //out << "# disposed" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << disposed << endl;
    in >> disposed;
    in.get(); // skip enter code.
    
    //out << "# moved" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << moved << endl;
    in >> moved;
    in.get(); // skip enter code.
   
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
    
//    //out << "# disposable" << endl;
//    in.getline(buf, MAX_LEN_BUF); // skip comment
//    //out << disposable << endl;
//    in >> disposable;
//    in.get(); // skip enter code.
    
    //board = sim->board;
    //?????????????????????????????????????????????????????????????????????????? where(when) is the board reference? bring it.
}

#define NUM_ITEM_TYPES 9
Item *createRandomItem() {
    int randomType = rand() % NUM_ITEM_TYPES;
    
    if (randomType == 0) {
        return new Potion();
    }
    else if (randomType == 1) {
        return new Expotion();
    }
    else if (randomType == 2) {
        return new Bounceshoe();
    }
    else if (randomType == 3) {
        return createRandomArmorByShape(ITEM_SHAPE_NONE);
    }
    else if (randomType == 4) {
        return createRandomWeaponByShape(ITEM_SHAPE_NONE);
    }
	else if (randomType == 5) {
		return new Key();
	}
    else if (randomType == 6) {
        return new Arrow();
    }
    else if (randomType == 7) {
        return new Bomb();
    }
	else if (randomType == 8) {
		return new Torch();
	}
    else {
        cout << "fatal error: Item::createRandomItem(): no such item type" << endl;
        exit(1);
    }
    
    return NULL;
}

Item *createItemByShape(char shape) {
    if (shape == DEFAULT_POTION_SHAPE) {
        return new Potion();
    }
	else if (shape == DEFAULT_EXPOTION_SHAPE) {
		return new Expotion();
	}
    else if (shape == DEFAULT_BOUNCESHOE_SHAPE) {
        return new Bounceshoe();
    }
	else if (shape == DEFAULT_KEY_SHAPE) {
		return new Key();
	}
    else if (isArmor(shape)) {
        return createRandomArmorByShape(shape);
    }
    else if (isWeapon(shape)) {
        return createRandomWeaponByShape(shape);
    }
    else if (shape == DEFAULT_ARROW_SHAPE_N ||
             shape == DEFAULT_ARROW_SHAPE_E ||
             shape == DEFAULT_ARROW_SHAPE_S ||
             shape == DEFAULT_ARROW_SHAPE_W) {
        return new Arrow(shape);
    }
    else if (shape == DEFAULT_BOMB_SHAPE) {
        return new Bomb();
    }
	else if (shape == DEFAULT_TORCH_SHAPE) {
		return new Torch();
	}

    return NULL;
}

Item *createItemByID(string itemID) {
    if (itemID == ITEM_ID_POTION) {
        return new Potion();
    }
    else if (itemID == ITEM_ID_EXPOTION) {
        return new Expotion();
    }
    else if (itemID == ITEM_ID_ARMOR) {
        return new Armor();
    }
    else if (itemID == ITEM_ID_WEAPON) {
        return new Weapon();
    }
    else if (itemID == ITEM_ID_BOUNCESHOE) {
        return new Bounceshoe();
    }
	else if (itemID == ITEM_ID_KEY) {
		return new Key();
	}
    else if (itemID == ITEM_ID_ARROW) {
        return new Arrow();
    }
    else if (itemID == ITEM_ID_BOMB) {
        return new Bomb();
    }
	else if (itemID == ITEM_ID_TORCH) {
		return new Torch();
	}
    else {
        cout << "error: no such item exist : itemID=" << itemID << endl;
        return NULL;
    }
}

//==============================================================================
//==============================================================================
//==============================================================================
// 2nd Generation
//==============================================================================
//==============================================================================
//==============================================================================

//------------------------------------------------------------------------------
// class ConsumableItem
//------------------------------------------------------------------------------
ConsumableItem::ConsumableItem() : Item('\0', "", 0, false) {
}

ConsumableItem::ConsumableItem(const ConsumableItem &other) : Item(other) {
}

ConsumableItem::ConsumableItem(char shape, string name, int price, bool disposable)
    : Item(shape, name, price, disposable) {
}

ConsumableItem::~ConsumableItem() {
}

void ConsumableItem::printFullSpec() const {
    Item::printFullSpec();
}

bool ConsumableItem::isConsumable() const {
    return true;
}

void ConsumableItem::save(ostream &out) const {
    Item::save(out);
    out << "#-------------------- class ConsumableItem" << endl;
}

void ConsumableItem::load(istream &in) {
    Item::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class ConsumableItem" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}

//------------------------------------------------------------------------------
// class EquippableItem
//------------------------------------------------------------------------------
EquippableItem::EquippableItem() : Item('\0', "", 0, false) {
    durability = 0;
}

EquippableItem::EquippableItem(const EquippableItem &other) : Item(other) {
}

EquippableItem::EquippableItem(char shape, string name, int price, bool disposable, int durability)
    : Item(shape, name, price, disposable) {
    this->durability = durability;
}

EquippableItem::~EquippableItem() {
}

void EquippableItem::printFullSpec() const {
    Item::printFullSpec();
    cout << " durability(" << durability << ")";
}

bool EquippableItem::isEquippable() const {
    return true;
}

void EquippableItem::save(ostream &out) const {
    Item::save(out);
    out << "#-------------------- class EquippableItem" << endl;
    
    out << "# durability" << endl;
    out << durability << endl;
}

void EquippableItem::load(istream &in) {
    Item::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class EquippableItem" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# durability" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << durability << endl;
    in >> durability;
    in.get(); // skip enter code.
}   

//==============================================================================
//==============================================================================
//==============================================================================
// 3rd Generation
//==============================================================================
//==============================================================================
//==============================================================================

//------------------------------------------------------------------------------
// class Potion
//------------------------------------------------------------------------------
Potion::Potion()
    : ConsumableItem(DEFAULT_POTION_SHAPE, DEFAULT_POTION_NAME, DEFAULT_POTION_PRICE, false) {
    hp = DEFAULT_POTION_HP;
    mp = DEFAULT_POTION_MP;
}

Potion::Potion(const Potion &other) : ConsumableItem(other) {
    hp = other.hp;
    mp = other.mp;
}

Potion::Potion(char shape, string name, int price, bool disposable, int hp, int mp)
    : ConsumableItem(shape, name, price, disposable) {
    this->hp = hp;
    this->mp = mp;
}

Potion::~Potion() {
}

void Potion::printFullSpec() const {
    ConsumableItem::printFullSpec();
    cout << " hp(" << hp << ") mp(" << mp << ")";
}

bool Potion::isPotion() const {
	return true;
}

string Potion::getID() const {
    return string(ITEM_ID_POTION);
}

bool Potion::use(Unit *unit) {
    if (unit == NULL) {
        return false;
    }
    
    unit->incHp(hp);
    unit->incMp(mp);
	
    disposed = true;
    return true;
}

Item *Potion::clone() const {
    return new Potion(*this);
}

void Potion::save(ostream &out) const {
    ConsumableItem::save(out);
    out << "#-------------------- class Potion" << endl;
    
    out << "# hp" << endl;
    out << hp << endl;
    out << "# mp" << endl;
    out << mp << endl;
}

void Potion::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Potion" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# hp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << hp << endl;
    in >> hp;
    in.get(); // skip enter code.
    
    //out << "# mp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << mp << endl;
    in >> mp;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Arrow
//------------------------------------------------------------------------------
Arrow::Arrow()
    : ConsumableItem(DEFAULT_ARROW_SHAPE_N, DEFAULT_ARROW_NAME, DEFAULT_ARROW_PRICE, false) {
    dir = DIR_NONE;
    atk = DEFAULT_ARROW_ATK;
        
    speed = DEFAULT_ARROW_SPEED;
    visited = false;
}

Arrow::Arrow(const Arrow &other) : ConsumableItem(other) {
    dir = other.dir;
    atk = other.atk;
    
    speed = other.speed;
    visited = other.visited;
}

Arrow::Arrow(char shape) : ConsumableItem(shape, DEFAULT_ARROW_NAME, DEFAULT_ARROW_PRICE, false)  {
    dir = DIR_NONE;
    atk = DEFAULT_ARROW_ATK;
    
    speed = DEFAULT_ARROW_SPEED;
    visited = false;
}

Arrow::Arrow(int dir, int atk)
    : ConsumableItem(DEFAULT_ARROW_SHAPE_N, DEFAULT_ARROW_NAME, DEFAULT_ARROW_PRICE, false) {
    this->dir = dir;
    this->atk = atk;
        
    speed = DEFAULT_ARROW_SPEED;
    visited = false;
}

Arrow::~Arrow() {
}

void Arrow::print() const {
    if (dir == DIR_N) {
        cout << DEFAULT_ARROW_SHAPE_N;
    }
    else if (dir == DIR_E) {
        cout << DEFAULT_ARROW_SHAPE_E;
    }
    else if (dir == DIR_S) {
        cout << DEFAULT_ARROW_SHAPE_S;
    }
    else if (dir == DIR_W) {
        cout << DEFAULT_ARROW_SHAPE_W;
    }
    else {
        cout << shape;
    }
}

void Arrow::printFullSpec() const {
    ConsumableItem::printFullSpec();
    cout << " atk(" << atk << ")";
}

bool Arrow::isVisited() const {
    return visited;
}

void Arrow::resetVisited() {
    visited = false;
}

void Arrow::fly() {
    visited = true;
    
    int nextRow = -1;
    int nextCol = -1;
    
    if (this->dir == DIR_N) {
        nextRow = row - 1;
        nextCol = col;
    }
    else if (this->dir == DIR_E) {
        nextRow = row;
        nextCol = col + 1;
    }
    else if (this->dir == DIR_S) {
        nextRow = row + 1;
        nextCol = col;
    }
    else if (this->dir == DIR_W) {
        nextRow = row;
        nextCol = col - 1;
    }
    else {
        return;
    }
    
    // if the next position is empty
    if (sim->board->validate(nextRow, nextCol) &&
        sim->board->getProp(nextRow, nextCol) == NULL &&
        sim->board->getUnit(nextRow, nextCol) == NULL &&
        sim->board->getThrowableItem(nextRow, nextCol) == NULL) {
        sim->board->setThrowableItem(row, col, NULL);
        sim->board->setThrowableItem(nextRow, nextCol, this);
    }
    else {
        if (sim->board->validate(nextRow, nextCol) &&
            sim->board->getUnit(nextRow, nextCol) != NULL &&
            sim->board->getUnit(nextRow, nextCol)->isMonster()) {
            sim->board->getUnit(nextRow, nextCol)->decHp(atk);
        }
        sim->board->setThrowableItem(row, col, NULL);
        delete this;
    }
}

bool Arrow::isThrowableItem() const {
    return true;
}

bool Arrow::isArrow() const {
    return true;
}

string Arrow::getID() const {
    return string(ITEM_ID_ARROW);
}

bool Arrow::use(Unit *unit) {
    /*
    if (unit == NULL) {
        return false;
    }
    
    unit->incHp(hp);
    unit->incMp(mp);
    
    disposed = true;
     return true;

     */
    return false;
}

Item *Arrow::clone() const {
    return new Arrow(*this);
}

void Arrow::save(ostream &out) const {
    ConsumableItem::save(out);
    out << "#-------------------- class Arrow" << endl;
    
    out << "# dir" << endl;
    out << dir << endl;
    out << "# atk" << endl;
    out << atk << endl;
}

void Arrow::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Arrow" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# dir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << dir << endl;
    in >> dir;
    in.get(); // skip enter code.
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Expotion
//------------------------------------------------------------------------------
Expotion::Expotion()
    : ConsumableItem(DEFAULT_EXPOTION_SHAPE, DEFAULT_EXPOTION_NAME, DEFAULT_EXPOTION_PRICE, false) {
	exp = DEFAULT_EXPOTION_EXP;
}

Expotion::Expotion(const Expotion &other) : ConsumableItem(other) {
    exp = other.exp;
}

Expotion::Expotion(char shape, string name, int price, bool disposable, int exp)
    : ConsumableItem(shape, name, price, disposable) {
	this->exp = exp;
}

Expotion::~Expotion() {
}

void Expotion::printFullSpec() const {
    ConsumableItem::printFullSpec();
    cout << " exp(" << exp << ")";
}

bool Expotion::isExpotion() const {
	return true;
}

string Expotion::getID() const {
    return string(ITEM_ID_EXPOTION);
}

bool Expotion::use(Unit *unit) {
	if (unit == NULL) {
		return false;
	}
	
	unit->incExp(exp);
	
	disposed = true;
	return true;
}

Item *Expotion::clone() const {
    return new Expotion(*this);
}

void Expotion::save(ostream &out) const {
    ConsumableItem::save(out);
    out << "#-------------------- class Expotion" << endl;
    
    out << "# exp" << endl;
    out << exp << endl;
}

void Expotion::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Expotion" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# exp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << exp << endl;
    in >> exp;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Armor
//------------------------------------------------------------------------------
Armor::Armor()
    : EquippableItem(DEFAULT_ARMOR_SHAPE, DEFAULT_ARMOR_NAME,
                     DEFAULT_ARMOR_PRICE, false, DEFAULT_ARMOR_DURABILITY) {
    def = DEFAULT_ARMOR_DEF;
    bodyPartID = DEFAULT_ARMOR_BODYPARTID;
}

Armor::Armor(const Armor &other) : EquippableItem(other) {
    def = other.def;
    bodyPartID = other.bodyPartID;
}

Armor::Armor(char shape, string name, int price, bool disposable, int durability, int def, int bodyPartID)
    : EquippableItem(shape, name, price, disposable, durability) {
    this->def = def;
    this->bodyPartID = bodyPartID;
}

Armor::~Armor() {
}

void Armor::printFullSpec() const {
    EquippableItem::printFullSpec();
    cout << " def(" << def << ")";
}

int Armor::getDef() {
    return def;
}

int Armor::getBodyPartID() {
    return bodyPartID;
}

bool Armor::isArmor() const {
    return true;
}

string Armor::getID() const {
    return string(ITEM_ID_ARMOR);
}

bool Armor::use(Unit *unit) {
    if (unit->equip(this)) {
        moved = true;
        return true;
    }
    else {
        return false;
    }
}

Item *Armor::clone() const {
    return new Armor(*this);
}

void Armor::save(ostream &out) const {
    EquippableItem::save(out);
    out << "#-------------------- class Armor" << endl;
    
    out << "# def" << endl;
    out << def << endl;
    out << "# bodyPartID" << endl;
    out << bodyPartID << endl;
}

void Armor::load(istream &in) {
    EquippableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Armor" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# def" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << def << endl;
    in >> def;
    in.get(); // skip enter code.
    
    //out << "# bodyPartID" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << bodyPartID << endl;
    in >> bodyPartID;
    in.get(); // skip enter code.
}

Armor *createRandomArmor() {
    return createRandomArmor(ITEM_SHAPE_NONE);
}

/*
 // class Paperdoll/Item related
 #define BODY_PART_ID_NONE 0
 #define BODY_PART_ID_HEAD 1
 #define BODY_PART_ID_CHEST 2
 #define BODY_PART_ID_BACK 3
 #define BODY_PART_ID_HANDS 4
 #define BODY_PART_ID_LEGS 5
 #define BODY_PART_ID_FEET 6
 
 #define ARMOR_SHAPE_HEAD 'A'
 #define ARMOR_SHAPE_CHEST 'W'
 #define ARMOR_SHAPE_BACK 'Q'
 #define ARMOR_SHAPE_HANDS 'U'
 #define ARMOR_SHAPE_LEGS 'L'
 #define ARMOR_SHAPE_FEET 'F'
 */
#define NUM_RANDOM_ARMORS 7
Armor *createRandomArmor(char shapeToCreate) {
    char shape[NUM_RANDOM_ARMORS] =             {ARMOR_SHAPE_HEAD,  ARMOR_SHAPE_FEET,       ARMOR_SHAPE_CHEST,      ARMOR_SHAPE_HEAD,   ARMOR_SHAPE_HANDS,  ARMOR_SHAPE_BACK,   ARMOR_SHAPE_LEGS};
    char name[NUM_RANDOM_ARMORS][80] =          {"Wizard\'s Hat",   "Poseidon\'s Boots",    "Zeus\' Chest",         "Zeus\' Helm",      "Zeus\' Gloves",    "Zeus\' Cape",      "Zeus\' Grieves"};
    int price[NUM_RANDOM_ARMORS] =              {100,               1000,                   100000,                 100000,             100000,             100000,             100000};
    int duarability[NUM_RANDOM_ARMORS] =        {100,               1000,                   100000,                 100000,             100000,             100000,             100000};
    int def[NUM_RANDOM_ARMORS] =                {1,                 100,                    1000,                   1000,               1000,               1000,               1000};
    int bodyPartID[NUM_RANDOM_ARMORS] =         {BODY_PART_ID_HEAD, BODY_PART_ID_FEET,      BODY_PART_ID_CHEST,     BODY_PART_ID_HEAD,  BODY_PART_ID_HANDS, BODY_PART_ID_BACK,  BODY_PART_ID_LEGS};
    
    int randIndex = -1;
    if (shapeToCreate == ITEM_SHAPE_NONE) {
        randIndex = rand() % NUM_RANDOM_ARMORS;
    }
    else {
        while (true) {
            randIndex = rand() % NUM_RANDOM_ARMORS;
            
            if (shape[randIndex] == shapeToCreate) {
                break;
            }
        }
    }
    
    return new Armor(shape[randIndex],
                     name[randIndex],
                     price[randIndex],
                     false,
                     duarability[randIndex],
                     def[randIndex],
                     bodyPartID[randIndex]);
}

Armor *createRandomArmorByShape(char shape) {
    return createRandomArmor(shape);
}

bool isArmor(char shape) {
    return 
        ARMOR_SHAPE_HEAD == shape ||
        ARMOR_SHAPE_CHEST == shape ||
        ARMOR_SHAPE_BACK == shape ||
        ARMOR_SHAPE_HANDS == shape ||
        ARMOR_SHAPE_LEGS == shape ||
        ARMOR_SHAPE_FEET == shape;
}

//------------------------------------------------------------------------------
// class Weapon
//------------------------------------------------------------------------------
Weapon::Weapon()
    : EquippableItem(DEFAULT_WEAPON_SHAPE, DEFAULT_WEAPON_NAME,
                 DEFAULT_WEAPON_PRICE, false, DEFAULT_WEAPON_DURABILITY) {
    atk = DEFAULT_WEAPON_ATK;
    numHands = DEFAULT_WEAPON_NUM_HANDS;
}

Weapon::Weapon(const Weapon &other) : EquippableItem(other) {
    atk = other.atk;
    numHands = other.numHands;
}

Weapon::Weapon(char shape, string name, int price, bool disposable, int durability, int atk, int numHands)
    : EquippableItem(shape, name, price, disposable, durability) {
    this->atk = atk;
    this->numHands = numHands;
}

Weapon::~Weapon() {
}

void Weapon::printFullSpec() const {
    EquippableItem::printFullSpec();
    cout << " atk(" << atk << ")";
}

int Weapon::getAtk() {
    return atk;
}

int Weapon::getNumHands() {
    return numHands;
}

bool Weapon::isWeapon() const {
    return true;
}

bool Weapon::isBow() const {
    return shape == WEAPON_SHAPE_TWO_HANDED_BOW;
}

string Weapon::getID() const {
    return string(ITEM_ID_WEAPON);
}

bool Weapon::use(Unit *unit) {
    if (unit->equip(this)) {
        moved = true;
        return true;
    }
    else {
        return false;
    }
}

void Weapon::save(ostream &out) const {
    EquippableItem::save(out);
    out << "#-------------------- class Weapon" << endl;
    
    out << "# atk" << endl;
    out << atk << endl;
    out << "# numHands" << endl;
    out << numHands << endl;
}

void Weapon::load(istream &in) {
    EquippableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Weapon" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
    
    //out << "# numHands" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numHands << endl;
    in >> numHands;
    in.get(); // skip enter code.
}

Weapon *createRandomWeapon() {
    return createRandomWeapon(ITEM_SHAPE_NONE);
}

Item *Weapon::clone() const {
    return new Weapon(*this);
}

/*
 // class Paperdoll/Item related
 #define BODY_PART_ID_LEFT_HAND 7
 #define BODY_PART_ID_RIGHT_HAND 8
 
 #define WEAPON_ONE_HAND 1
 #define WEAPON_TWO_HAND 2
 
 #define WEAPON_SHAPE_ONE_HAND '!'
 #define WEAPON_SHAPE_TWO_HAND '?'
 */
#define NUM_RANDOM_WEAPONS 4
Weapon *createRandomWeapon(char shapeToCreate) {
    char shape[NUM_RANDOM_WEAPONS] =             {WEAPON_SHAPE_ONE_HAND,     WEAPON_SHAPE_ONE_HAND,      WEAPON_SHAPE_TWO_HAND, WEAPON_SHAPE_TWO_HANDED_BOW};
    char name[NUM_RANDOM_WEAPONS][80] =          {"Wizard\'s Wand",          "Poseidon\'s Sword",        "Zeus\' Staff",        "Apollo\' Bow"};
    int price[NUM_RANDOM_WEAPONS] =              {100,                       1000,                       100000,                1000000};
    int duarability[NUM_RANDOM_WEAPONS] =        {100,                       1000,                       100000,                1000000};
    int atk[NUM_RANDOM_WEAPONS] =                {1,                         100,                        1000,                  1000};
    int numHands[NUM_RANDOM_WEAPONS] =           {WEAPON_ONE_HAND,           WEAPON_ONE_HAND,            WEAPON_TWO_HAND,       WEAPON_TWO_HAND};
    
    int randIndex = -1;
    if (shapeToCreate == ITEM_SHAPE_NONE) {
        randIndex = rand() % NUM_RANDOM_WEAPONS;
    }
    else {
        while (true) {
            randIndex = rand() % NUM_RANDOM_WEAPONS;
            
            if (shape[randIndex] == shapeToCreate) {
                break;
            }
        }
    }
    
    return new Weapon(shape[randIndex],
                      name[randIndex],
                      price[randIndex],
                      false,
                      duarability[randIndex],
                      atk[randIndex],
                      numHands[randIndex]);
}

Weapon *createRandomWeaponByShape(char shape) {
    return createRandomWeapon(shape);
}

bool isWeapon(char shape) {
    return 
        WEAPON_SHAPE_ONE_HAND == shape ||
        WEAPON_SHAPE_TWO_HAND == shape;
}

//------------------------------------------------------------------------------
// class Bow
//------------------------------------------------------------------------------
/*
Bow::Bow()
	: EquippableItem(DEFAULT_BOW_SHAPE, DEFAULT_BOW_NAME,
		DEFAULT_BOW_PRICE, DEFAULT_BOW_DURABILITY) {
	atk = DEFAULT_BOW_ATK;
	numHands = DEFAULT_BOW_NUM_HANDS;
}

Bow::Bow(const Bow &other) : EquippableItem(other) {
	atk = other.atk;
	numHands = other.numHands;
}

Bow::Bow(char shape, string name, int price, int durability, int atk, int numHands)
	: EquippableItem(shape, name, price, durability) {
	this->atk = atk;
	this->numHands = numHands;
}

Bow::~Bow() {
}

void Bow::printFullSpec() const {
	EquippableItem::printFullSpec();
	cout << " atk(" << atk << ")";
}

int Bow::getAtk() {
	return atk;
}

int Bow::getNumHands() {
	return numHands;
}

bool Bow::isBow() const {
	return true;
}

string Bow::getID() const {
	return string(ITEM_ID_BOW);
}

bool Bow::use(Unit *unit) {
	if (unit->equip(this)) {
		moved = true;
		return true;
	}
	else {
		return false;
	}
}

void Bow::save(ostream &out) const {
	EquippableItem::save(out);
	out << "#-------------------- class Bow" << endl;

	out << "# atk" << endl;
	out << atk << endl;
	out << "# numHands" << endl;
	out << numHands << endl;
}

void Bow::load(istream &in) {
	EquippableItem::load(in);

	char buf[MAX_LEN_BUF];

	//out << "#-------------------- class Bow" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment

								  //out << "# atk" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
								  //out << atk << endl;
	in >> atk;
	in.get(); // skip enter code.

			  //out << "# numHands" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
								  //out << numHands << endl;
	in >> numHands;
	in.get(); // skip enter code.
}



Item *Bow::clone() const {
	return new Bow(*this);
}

*/

//------------------------------------------------------------------------------
// class Bounceshoe
//------------------------------------------------------------------------------
Bounceshoe::Bounceshoe()
    : Armor(DEFAULT_BOUNCESHOE_SHAPE, DEFAULT_BOUNCESHOE_NAME,
            DEFAULT_BOUNCESHOE_PRICE, false, DEFAULT_BOUNCESHOE_DURABILITY,
            DEFAULT_BOUNCESHOE_DEF, DEFAULT_BOUNCESHOE_BODYPARTID) {
    range = rand() % MAX_BOUNCESHOE_RANGE + 1;
}

Bounceshoe::Bounceshoe(const Bounceshoe &other) : Armor(other) {
    range = other.range;
}

Bounceshoe::Bounceshoe(char shape, string name, int price, bool disposable, int durability,
                       int def, int bodyPartID, int range)
    : Armor(shape, name, price, disposable, durability, def, bodyPartID) {
    this->range = range;
}

Bounceshoe::~Bounceshoe() {
}

void Bounceshoe::printFullSpec() const {
    Armor::printFullSpec();
    cout << " range(" << range << ")";
}

int Bounceshoe::getRange() const {
    return range;
}

bool Bounceshoe::isBounceshoe() const {
	return true;
}

string Bounceshoe::getID() const {
    return string(ITEM_ID_BOUNCESHOE);
}

bool Bounceshoe::use(Unit *unit) {
	if (unit == NULL) {
		return false;
	}

    disposed = false;
	return true;
}

Item *Bounceshoe::clone() const {
    return new Bounceshoe(*this);
}

void Bounceshoe::save(ostream &out) const {
    EquippableItem::save(out);
    out << "#-------------------- class Bounceshoe" << endl;
    
    out << "# range" << endl;
    out << range << endl;
}

void Bounceshoe::load(istream &in) {
    EquippableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Bounceshoe" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# range" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << range << endl;
    in >> range;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Key
//------------------------------------------------------------------------------
Key::Key()
	: ConsumableItem(DEFAULT_KEY_SHAPE, DEFAULT_KEY_NAME, DEFAULT_KEY_PRICE, false) {

}

Key::Key(const Key &other) : ConsumableItem(other) {
	
}

Key::Key(char shape, string name, int price, bool disposable, int hp, int mp)
	: ConsumableItem(shape, name, price, disposable) {
	
}

Key::~Key() {
}

void Key::printFullSpec() const {
	ConsumableItem::printFullSpec();
	
}

bool Key::isKey() const {
	return true;
}

string Key::getID() const {
	return string(ITEM_ID_KEY);
}

bool Key::use(Unit *unit) {
	if (unit == NULL) {
		return false;
	}


	disposed = false;
	return true;
}

Item *Key::clone() const {
	return new Key(*this);
}

void Key::save(ostream &out) const {
	Item::save(out);
	out << "#-------------------- class ConsumableItem" << endl;
}

void Key::load(istream &in) {
	Item::load(in);

	char buf[MAX_LEN_BUF];

	//out << "#-------------------- class ConsumableItem" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
}

//------------------------------------------------------------------------------
// class Bomb
//------------------------------------------------------------------------------

Bomb::Bomb() : ConsumableItem(DEFAULT_BOMB_SHAPE, DEFAULT_BOMB_NAME,
                              DEFAULT_BOMB_PRICE, DEFAULT_BOMB_DISPOSABLE) {
    range = DEFAULT_BOMB_RANGE;
    atk = DEFAULT_BOMB_ATK;
}

Bomb::Bomb(const Bomb &other) : ConsumableItem(other) {
    range = other.range;
    atk = other.atk;
}

Bomb::Bomb(char shape, string name, int price, bool disposable,
           int range, int atk)
    : ConsumableItem(shape, name, price, DEFAULT_BOMB_DISPOSABLE) {
    this->range = range;
    this->atk = atk;
}

Bomb::~Bomb() {
}

void Bomb::printFullSpec() {
    ConsumableItem::printFullSpec();
    
    cout << " Atk(" << setw(4) << atk << ")";
}

void Bomb::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    out << BLACK;
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}
bool Bomb::isBomb() const {
	return true;
}
string Bomb::getID() const {
    return ITEM_ID_BOMB;
}

//Shockwave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
//          int row, int col, int range, int frameInterval, char fxShape,
//          int skillNumber);
//void startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
//               int row, int col, int skillNumber);
bool Bomb::use(Unit *unit) {

	sim->eventQueue->enqueue(new TimeBomb());

    if (disposable) {
        moved = true;
    }
    return true;
}

void Bomb::effect(Unit *unit, Item *item, Prop *prop) {
    if (unit != NULL) {
        if (unit->isMonster()) {
            unit->decHp(atk);
            if (unit->isDead()) {
            }
        }
    }
}

Item *Bomb::clone() const {
    return new Bomb(*this);
}

void Bomb::save(ostream &out) const {
	Item::save(out);
	out << "#-------------------- class ConsumableItem" << endl;
}

void Bomb::load(istream &in) {
	Item::load(in);

	char buf[MAX_LEN_BUF];

	//out << "#-------------------- class ConsumableItem" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
}
//------------------------------------------------------------------------------
// class Torch
//------------------------------------------------------------------------------
Torch::Torch()
	: ConsumableItem(DEFAULT_TORCH_SHAPE, DEFAULT_TORCH_NAME, DEFAULT_TORCH_PRICE, false) {

}

Torch::Torch(const Torch &other) : ConsumableItem(other) {

}

Torch::Torch(char shape, string name, int price, bool disposable, int hp, int mp)
	: ConsumableItem(shape, name, price, disposable) {

}

Torch::~Torch() {
}

void Torch::printFullSpec() const {
	ConsumableItem::printFullSpec();

}


bool Torch::isTorch() const {
	return true;
}

string Torch::getID() const {
	return string(ITEM_ID_TORCH);
}

bool Torch::use(Unit *unit) {
	if (unit == NULL) {
		return false;
	}
	
	sim->board->activateTorch();
	disposed = true;
	return true;
}

Item *Torch::clone() const {
	return new Torch(*this);
}

void Torch::save(ostream &out) const {
	Item::save(out);
	out << "#-------------------- class ConsumableItem" << endl;
}

void Torch::load(istream &in) {
	Item::load(in);

	char buf[MAX_LEN_BUF];

	//out << "#-------------------- class ConsumableItem" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
}

