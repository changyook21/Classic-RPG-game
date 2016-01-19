#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "item.h"
#include "board.h"
#include "unit.h"
#include "monster.h"
#include "inventory.h"
#include "backpack.h"
#include "paperdoll.h"
#include "util.h"
#include "prop.h"

//extern Board *sim->board;
#include "sim.h"
extern Sim *sim;

//------------------------------------------------------------------------------
// class Unit
//------------------------------------------------------------------------------
Unit::Unit() {
    shape = '\0';
    
    row = -1;
    col = -1;
    
    maxHp = 0;
    hp = 0;
    maxMp = 0;
    mp = 0;
    atk = 0;
    def = 0;
    gold = 0;
    exp = 0;
    
    died = false;
    frozen = false;

    unitEngaged = NULL;
}

Unit::Unit(char shape) {
    this->shape = shape;
    
    row = -1;
    col = -1;

    maxHp = 0;
    hp = 0;
    maxMp = 0;
    mp = 0;
    atk = 0;
    def = 0;
    gold = 0;
    exp = 0;
    
    died = false;
    frozen = false;

    unitEngaged = NULL;
}

Unit::Unit(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
           int atk, int def, int gold, int exp) {
    this->shape = shape;
    
    this->row = row;
    this->col = col;
    
    this->maxHp = maxHp;
    this->hp = hp;
    this->maxMp = maxMp;
    this->mp = mp;
    this->atk = atk;
    this->def = def;
    this->gold = gold;
    this->exp = exp;
    
    died = false;
    frozen = false;
    
    unitEngaged = NULL;
}

Unit::~Unit() {
}

void Unit::reset() {
    hp = maxHp;
    mp = maxMp;
    
    died = false;
    frozen = false;
    
    unitEngaged = NULL;
}

void Unit::print() {
    cout << shape;
}

void Unit::printStat() {
    cout << shape << ": HP(" << hp << ") MP(" << mp
         << ") ATK(" << atk << ") DEF(" << def
         << ") GOLD(" << gold << ") EXP(" << exp << ")";
}

int Unit::getRow() {
    return row;
}

void Unit::setRow(int row) {
    this->row = row;
}

int Unit::getCol() {
    return col;
}

void Unit::setCol(int col) {
    this->col = col;
}

int Unit::getHp() {
    return hp;
}

void Unit::incHp(int hpToInc) {
    if (hp + hpToInc >= maxHp) {
        hp = maxHp;
    }
    else {
        hp += hpToInc;
    }
}

void Unit::decHp(int hpToDec) {
    if (hp - hpToDec <= 0) {
        hp = 0;
        died = true;
    }
    else {
        hp -= hpToDec;
    }
}

int Unit::getMp() {
    return mp;
}

void Unit::incMp(int mpToInc) {
    if (mp + mpToInc >= maxMp) {
        mp = maxMp;
    }
    else {
        mp += mpToInc;
    }
}

void Unit::decMp(int mpToDec) {
    if (mp - mpToDec <= 0) {
        mp = 0;
    }
    else {
        mp -= mpToDec;
    }
}

int Unit::getAtk() {
    return atk;
}

void Unit::incAtk(int atkToInc) {
    atk += atkToInc;
}

void Unit::decAtk(int atkToDec) {
    atk -= atkToDec;
}

int Unit::getDef() {
    return def;
}

void Unit::incDef(int defToInc) {
    def += defToInc;
}

void Unit::decDef(int defToDec) {
    def -= defToDec;
}

int Unit::getGold() {
    return gold;
}

void Unit::incGold(int goldToInc) {
    gold += goldToInc;
}

// pre-condtion: def - defToDec < 0
void Unit::decGold(int goldToDec) {
    gold -= goldToDec;
}

int Unit::getExp() {
    return exp;
}

void Unit::incExp(int expToInc) {
    exp += expToInc;
}

bool Unit::isDead() {
    return died;
}

void Unit::setDied(bool died) {
    this->died = died;
}

bool Unit::getFrozen() {
    return frozen;
}

void Unit::setFrozen(bool frozen) {
    this->frozen = frozen;
}

Unit *Unit::getUnitEngaged() {
    return unitEngaged;
}

void Unit::setUnitEngaged(Unit *unitEngaged) {
    this->unitEngaged = unitEngaged;
}

// for the fake function body, return negative return value(false, 0, -1, NULL, "", '\0',..)
bool Unit::isHero() {
    // N/A
    return false;
}

bool Unit::isMonster() {
    // N/A
    return false;
}
bool Unit::isGhost() {
	// N/A
	return false;
}

bool Unit::isBoss() {
    // N/A
    return false;
}

bool Unit::isMerchant() {
    // N/A
    return false;
}

void Unit::showItemsListToSell() {
    // N/A
}

Item *Unit::removeItemByIndex(int index) {
    // N/A
    return NULL;
}

bool Unit::receiveItem(Item *item) {
    // N/A
    return false;
}

bool Unit::equip(Item *item) {
    // N/A
    return false;
}

bool Unit::unequip(int bodyPartID) {
    // N/A
    return false;
}

void Unit::move(int dir, bool bounceKeyPressed) {
    // N/A
}

void Unit::save(ostream &out) {
    out << "#-------------------- class Unit" << endl;
    
    out << "# shape" << endl;
    out << shape << endl;
    out << "# row" << endl;
    out << row << endl;
    out << "# col" << endl;
    out << col << endl;
    out << "# maxHp" << endl;
    out << maxHp << endl;
    out << "# hp" << endl;
    out << hp << endl;
    out << "# maxMp" << endl;
    out << maxMp << endl;
    out << "# mp" << endl;
    out << mp << endl;
    out << "# atk" << endl;
    out << atk << endl;
    out << "# def" << endl;
    out << def << endl;
    out << "# gold" << endl;
    out << gold << endl;
    out << "# exp" << endl;
    out << exp << endl;
    out << "# died" << endl;
    out << died << endl;
    out << "# frozen" << endl;
    out << frozen << endl;

    //Unit *unitEngaged;
}

void Unit::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Unit" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# shape" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << shape << endl;
    in >> shape;
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
    
    //out << "# maxHp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxHp << endl;
    in >> maxHp;
    in.get(); // skip enter code.
    
    //out << "# hp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << hp << endl;
    in >> hp;
    in.get(); // skip enter code.
    
    //out << "# maxMp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxMp << endl;
    in >> maxMp;
    in.get(); // skip enter code.
    
    //out << "# mp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << mp << endl;
    in >> mp;
    in.get(); // skip enter code.
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
    
    //out << "# def" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << def << endl;
    in >> def;
    in.get(); // skip enter code.
    
    //out << "# gold" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << gold << endl;
    in >> gold;
    in.get(); // skip enter code.
    
    //out << "# exp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << exp << endl;
    in >> exp;
    in.get(); // skip enter code.
    
    //out << "# died" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << died << endl;
    in >> died;
    in.get(); // skip enter code.
    
    //out << "# frozen" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << frozen << endl;
    in >> frozen;
    in.get(); // skip enter code.
    
    //unitEngaged;
    //?????????????????????????????????????????????????????????????????????????? clear the pointer'
    unitEngaged = NULL;
}

Unit *createUnitByShape(char shape) {
    if (shape == DEFAULT_HERO_SHAPE) {
        return new Hero();
    }
    else if (shape == DEFAULT_MONSTER_SHAPE) {
        return new Monster();
    }
    else if (shape == DEFAULT_BOSS_SHAPE) {
        return new Boss();
    }
    else if (shape == DEFAULT_MERCHANT_SHAPE) {
        return new Merchant();
    }
	else if (shape == DEFAULT_GHOST_SHAPE) {
		return new Ghost();
	}
    return NULL;
}

Unit *createUnitByID(string unitID) {
    if (unitID == UNIT_ID_HERO) {
        return new Hero();
    }
    else if (unitID == UNIT_ID_MONSTER) {
        return new Monster();
    }
    else if (unitID == UNIT_ID_BOSS) {
        return new Boss();
    }
    else if (unitID == UNIT_ID_MERCHANT) {
        return new Merchant();
    }
	else if (unitID == UNIT_ID_GHOST) {
		return new Ghost();
	}
    
    return NULL;
}

//------------------------------------------------------------------------------
// class Hero
//------------------------------------------------------------------------------
Hero::Hero() : Unit(DEFAULT_HERO_SHAPE, -1, -1,
                    DEFAULT_HERO_MAX_HP, DEFAULT_HERO_HP,
                    DEFAULT_HERO_MAX_MP, DEFAULT_HERO_MP,
                    DEFAULT_HERO_ATK, DEFAULT_HERO_DEF,
                    DEFAULT_HERO_GOLD, DEFAULT_HERO_EXP) {
    initHero();
}

Hero::Hero(char shape) : Unit(shape, -1, -1,
                              DEFAULT_HERO_MAX_HP, DEFAULT_HERO_HP,
                              DEFAULT_HERO_MAX_MP, DEFAULT_HERO_MP,
                              DEFAULT_HERO_ATK, DEFAULT_HERO_DEF,
                              DEFAULT_HERO_GOLD, DEFAULT_HERO_EXP) {
    initHero();
}

void Hero::initHero() {
    slots = new Inventory();
    backpack = new Backpack();
    paperdoll = new Paperdoll();
    
	key = false;
    bounce = false;
    bounceRange = 0;

    dir = DIR_NONE;
}

Hero::~Hero() {
    destroyHero();
}

void Hero::destroyHero() {
    if (slots != NULL) {
        delete slots;
        slots = NULL;
    }
    if (backpack != NULL) {
        delete backpack;
        backpack = NULL;
    }
    if (paperdoll != NULL) {
        delete paperdoll;
        paperdoll = NULL;
    }

	key = false;
    bounce = false;
    bounceRange = 0;
}

void Hero::printStat() {
    Unit::printStat();
    cout << endl;
    
    cout << "Slots     : ";
    slots->print();
    cout << endl;
    
    cout << "Backpack  : ";
    backpack->print();
    cout << endl;
    
    cout << "Paperdoll : ";
    paperdoll->print();
    cout << endl;
    
    if (unitEngaged != NULL) {
        cout << "  vs  ";
        unitEngaged->printStat();
    }
    
    cout << endl;
}

bool Hero::isHero() {
    return true;
}

void Hero::showItemsListToSell() {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Slots <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    
    int curIndexSlots = 0;
    slots->resetIterator();
    
    while (slots->hasMore()) {
        Item *curItem = slots->next();
        cout << setw(3) << curIndexSlots << ": ";
        if (curItem != NULL) {
            curItem->printFullSpec();
        }
        else {
            cout << "<< Empty >>";
        }
        cout << endl;
        
        curIndexSlots++;
    }
    
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Backpack <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    
    int curIndexBackpack = 100;
    backpack->resetIterator();
    
    while (backpack->hasMore()) {
        Item *curItem = backpack->next();
        cout << setw(3) << curIndexBackpack << ": ";
        curItem->printFullSpec();
        cout << endl;
        
        curIndexBackpack++;
    }
}

Item *Hero::removeItemByIndex(int index) {
    // is the index for slots
    if (index >= 0 && index < slots->capacity()) {
        return slots->removeItemAt(index);
    }
    // is the index for backpack
    else if (index >= 100 && index < backpack->size()+100) {
        index -= 100;
        return backpack->removeItemAt(index);
    }
    
    return NULL;
}

bool Hero::receiveItem(Item *item) {
    if (!slots->isFull()) {
        slots->add(item);
    }
    else {
        backpack->add(item);
    }
    return true;
}

bool Hero::moveItemFromSlotsToBackpack(int indexItemOfSlots) {
    if (indexItemOfSlots < 0 && indexItemOfSlots >= slots->capacity()) {
        return false;
    }
    
    if (slots->getItemAt(indexItemOfSlots) == NULL) {
        return false;
    }
    
    backpack->add(slots->removeItemAt(indexItemOfSlots));
    
    return true;
}

bool Hero::moveItemFromBackpackToSlots(int indexItemOfBackpack, int indexItemOfSlots) {
    if (indexItemOfBackpack < 0 && indexItemOfBackpack >= backpack->capacity()) {
        return false;
    }
    
    if (backpack->getItemAt(indexItemOfBackpack) == NULL) {
        return false;
    }
    
    if (slots->getItemAt(indexItemOfSlots) != NULL) {
        return false;
    }
    
    Item *itemToMove = backpack->removeItemAt(indexItemOfBackpack);
    return slots->insertItemAt(indexItemOfSlots, itemToMove);
}

bool Hero::equip(Item *item) {
    if (item == NULL) {
        return false;
    }
    
    return paperdoll->equip(item, this);
}

bool Hero::unequip(int bodyPartID) {
    Item *item = paperdoll->unequip(bodyPartID, this);
    if (item != NULL) {
        backpack->add(item);
        return true;        
    }
    else {
        return false;
    }
}

void Hero::shoot() {
    if (dir != DIR_NONE) {
        if (paperdoll->getRightHand() != NULL &&
            paperdoll->getRightHand()->isBow()) {
            int rowDir = 0;
            int colDir = 0;
            
            if (dir == DIR_N) {
                rowDir = -1;
            }
            else if (dir == DIR_E) {
                colDir = 1;
            }
            else if (dir == DIR_S) {
                rowDir = 1;
            }
            else if (dir == DIR_W) {
                colDir = -1;
            }
            
            int nextRow = row+rowDir;
            int nextCol = col+colDir;
            
            if (sim->board->validate(nextRow, nextCol) &&
                sim->board->getProp(nextRow, nextCol) == NULL &&
                sim->board->getUnit(nextRow, nextCol) == NULL &&
                sim->board->getThrowableItem(nextRow, nextCol) == NULL) {
                Arrow *arrow = new Arrow(dir, paperdoll->getRightHand()->getAtk() / 10);
                sim->board->setThrowableItem(nextRow, nextCol, arrow); // 10% of bow's atk is applied.
            }
        }
    }
}

void Hero::move(int dir) {
    move(dir, false);
}

void Hero::move(int dir, bool bounceKeyPressed) {
    this->dir = dir;
    
    bool moved = false;

    int prevRow = row;
    int prevCol = col;

    int nextRow = -1;
    int nextCol = -1;
    
	if (bounce && bounceKeyPressed) {
        int rowDir = 0;
        int colDir = 0;
        
        if (dir == DIR_N) {
            rowDir = -1;
        }
        else if (dir == DIR_E) {
            colDir = 1;
        }
        else if (dir == DIR_S) {
            rowDir = 1;
        }
        else if (dir == DIR_W) {
            colDir = -1;
        }

        int curRow = row+rowDir;
        int curCol = col+colDir;
        
        if (sim->board->validate(curRow, curCol) &&
            sim->board->getProp(curRow, curCol) == NULL) {
            for (int i = 0; i < bounceRange+1; i++) {
                // hero stops when there is an item.
                if (sim->board->validate(curRow, curCol) &&
                    sim->board->getItem(curRow, curCol) != NULL) {
                    break;
                }
                // hero stops when there is a prop.
                else if (sim->board->validate(curRow, curCol) &&
                    sim->board->getProp(curRow, curCol) != NULL) {
                    curRow -= rowDir;
                    curCol -= colDir;
                    break;
                }
                
                if (i < bounceRange) {
                    curRow += rowDir;
                    curCol += colDir;
                }
            }
        }
        nextRow = curRow;
        nextCol = curCol; 
	}
	else {
		if (dir == DIR_N) {
			nextRow = row - 1;
			nextCol = col;
		}
		else if (dir == DIR_E) {
			nextRow = row;
			nextCol = col + 1;
		}
		else if (dir == DIR_S) {
			nextRow = row + 1;
			nextCol = col;
		}
		else if (dir == DIR_W) {
			nextRow = row;
			nextCol = col - 1;
		}
		else {
			return;
		}
	}
    
    // if the next position is empty
	if (sim->board->validate(nextRow, nextCol) &&
		(sim->board->getProp(nextRow, nextCol) == NULL ||
		 sim->board->getProp(nextRow, nextCol)->isClimbable()) &&
        sim->board->getUnit(nextRow, nextCol) == NULL) {
        sim->board->setUnit(row, col, NULL);
        sim->board->setUnit(nextRow, nextCol, this);
        moved = true;
		
    }
    
	// if the player has key to open door
	if (sim->board->validate(nextRow, nextCol) &&
		(sim->board->getProp(nextRow, nextCol) != NULL &&
		sim->board->getProp(nextRow, nextCol)->isDoor()) &&
		sim->board->getUnit(nextRow, nextCol) == NULL && key) {
		sim->board->setUnit(row, col, NULL);
		sim->board->setUnit(nextRow, nextCol, this);
	}

    // trigger of the climbable prop(portal)
	if (moved) {
        if (sim->board->getProp(prevRow, prevCol) != NULL) {
            sim->board->getProp(prevRow, prevCol)->deactivate(this);
        }
        
		if (sim->board->getProp(nextRow, nextCol) != NULL) {
			sim->board->getProp(nextRow, nextCol)->trigger(this);
		}
	}
	
    // trigger of the non-climbable prop(fountain)
    if (!moved) {
        if (sim->board->getProp(nextRow, nextCol) != NULL) {
            sim->board->getProp(nextRow, nextCol)->trigger(this);
        }
    }

    // unfreeze monsters when hero has been moved
    if (moved) {
        for (int i = prevRow-1; i <= prevRow+1; i++) {
            for (int j = prevCol-1; j <= prevCol+1; j++) {
                if (sim->board->getUnit(i, j) != NULL &&
                    sim->board->getUnit(i, j)->isMonster() &&
                    !sim->board->getUnit(i, j)->isBoss()) {
                    sim->board->getUnit(i, j)->setFrozen(false);
                }
            }
        }
    }
    
    // freeze monsters around hero
    if (moved) {
        for (int i = nextRow-1; i <= nextRow+1; i++) {
            for (int j = nextCol-1; j <= nextCol+1; j++) {
                if (sim->board->getUnit(i, j) != NULL &&
                    sim->board->getUnit(i, j)->isMonster() &&
                    !sim->board->getUnit(i, j)->isBoss()) {
                    sim->board->getUnit(i, j)->setFrozen(true);
                }
            }
        }
    }

    // pick up an item if there is one under my feet.
    if (moved) {
        if (sim->board->getItem(nextRow, nextCol) != NULL) {
            Item *item = sim->board->getItem(nextRow, nextCol);
            sim->board->setItem(nextRow, nextCol, NULL);
            if (!slots->isFull()) {
                slots->add(item);
            }
            else {
                backpack->add(item);
            }
            if (item->isBounceshoe()) {
                bounce = true;
                bounceRange = ((Bounceshoe *)item)->getRange();
            }
			if (item->isKey()) {
				key = true;
			}
        }
    }

    // interact wich the unit: battle, buying, selling,..
    if (!moved) {
        if (sim->board->getUnit(nextRow, nextCol) != NULL) {
            if (sim->board->getUnit(nextRow, nextCol)->isMonster()) { // monster or boss
                unitEngaged = sim->board->getUnit(nextRow, nextCol);
            }
            sim->board->getUnit(nextRow, nextCol)->interact(this);
        }
    }
}

void Hero::interact(Unit *unit) {
    // N/A
}

void Hero::useItem(int index) {
    slots->useItem(index, this);
}

void Hero::kickout() {
    
}

string Hero::getID() {
    return UNIT_ID_HERO;
}

void Hero::save(ostream &out) {
    Unit::save(out);
    
    out << "#-------------------- class Hero" << endl;
    
    slots->save(out);
    backpack->save(out);
    paperdoll->save(out);
    
    out << "# bounce" << endl;
    out << bounce << endl;
    out << "# bounceRange" << endl;
    out << bounceRange << endl;
}

void Hero::load(istream &in) {
    Unit::load(in);
    
    destroyHero();
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Hero" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    initHero();
    
    slots->load(in);
    backpack->load(in);
    paperdoll->load(in);
    
    //out << "# bounce" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << bounce << endl;
    in >> bounce;
    in.get(); // skip enter code.
    
    //out << "# bounceRange" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << bounceRange << endl;
    in >> bounceRange;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Merchant
//------------------------------------------------------------------------------
Merchant::Merchant() : Unit(DEFAULT_MERCHANT_SHAPE) {
    itemsToSell = new Backpack();
    itemsBought = new Backpack();
    
    for (int i = 0; i < 10; i++) {
        itemsToSell->add(createRandomItem());
    }
}

Merchant::Merchant(char shape) : Unit(shape) {
}

Merchant::~Merchant() {
}

bool Merchant::isMerchant() {
    return true;
}

void Merchant::move(int dir) {
}

void Merchant::interact(Unit *unit) {
    while (true) {
        cout << "(B)uy / (S)ell / (Q)uit : ";
        while (!_kbhit()) {}
#ifdef VISUAL_STUDIO
        char command = _getch();
#else
        char command = getchar();
#endif 
        if (command == 'b') {
            buy(unit);
        }
        else if (command == 's') {
            sell(unit);
        }
        else if (command == 'q') {
            return;
        }
    }
}

// the merchant is selling.
// hero is buying items from merchant
void Merchant::buy(Unit *unit) {
    // show menu buy
    while (true) {
        //----------------------------------------------------------------------
        // show the list of items
        //----------------------------------------------------------------------
        cout << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------------------- Merchant ------------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Items to Sell <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        
        int curIndexItemToSell = 0;
        itemsToSell->resetIterator();
        
        while (itemsToSell->hasMore()) {
            Item *curItem = itemsToSell->next();
            cout << setw(3) << curIndexItemToSell << ": ";
            curItem->printFullSpec();
            cout << endl;
            
            curIndexItemToSell++;
        }
        
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Items from you <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        
        int curIndexItemBought = 100;
        itemsBought->resetIterator();
        
        while (itemsBought->hasMore()) {
            Item *curItem = itemsBought->next();
            cout << setw(3) << curIndexItemBought << ": ";
            curItem->printFullSpec();
            cout << endl;
            
            curIndexItemBought++;
        }
        
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "--------------------------------- Hero's Stat ----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        
        //----------------------------------------------------------------------
        // show hero's stat
        //----------------------------------------------------------------------
        unit->printStat();
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        cout << "--------------------------------------------------------------------------------" << endl;
        int indexToBuy = -1;
        cout << "Enter the index of the item to buy (-1 to exit) : ";
        cin >> indexToBuy;
        
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        if (indexToBuy == -1) { // exit?
            cin.get();
            break;
        }
        // index of itemsToSell?
        if (indexToBuy >= 0 && indexToBuy < itemsToSell->size()) {
            if (unit->getGold() >= itemsToSell->getItemAt(indexToBuy)->getPrice()) {
                unit->decGold(itemsToSell->getItemAt(indexToBuy)->getPrice());
                unit->receiveItem(itemsToSell->getItemAt(indexToBuy)->clone());
            }
            else {
                cout << "error: You can't afford the price!" << endl;
            }
        }
        // index of itemsBought?
        else if (indexToBuy >= 100 && indexToBuy < itemsBought->size()+100) {
            indexToBuy -= 100;
            if (unit->getGold() >= itemsBought->getItemAt(indexToBuy)->getPrice()) {
                unit->decGold(itemsBought->getItemAt(indexToBuy)->getPrice());
                unit->receiveItem(itemsBought->removeItemAt(indexToBuy));
            }
            else {
                cout << "error: You can't afford the price!" << endl;
            }
        }
        else {
            cout << "error: invalid index!" << endl;
        }
    }
}

// merchant is buying items from hero
void Merchant::sell(Unit *unit) {
    // show menu buy
    while (true) {
        //----------------------------------------------------------------------
        // show the list of items of unit(hero)
        //----------------------------------------------------------------------
        cout << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------------------  Merchant -----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        unit->showItemsListToSell();
        
        //----------------------------------------------------------------------
        // show hero's stat
        //----------------------------------------------------------------------
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "--------------------------------- Hero's Stat ----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        unit->printStat();
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        cout << "--------------------------------------------------------------------------------" << endl;
        int indexToSell = -1;
        cout << "Enter the index of the item to sell (-1 to exit) : ";
        cin >> indexToSell;
        
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        if (indexToSell == -1) { // exit?
            cin.get();
            break;
        }
        
        // index of slots?
        Item *itemFromUnit = unit->removeItemByIndex(indexToSell);
        if (itemFromUnit != NULL) {
            unit->incGold(itemFromUnit->getPrice());
            itemsBought->add(itemFromUnit);
        }
        else {
            cout << "error: invalid index or no item!" << endl;
        }
    }
}

string Merchant::getID() {
    return UNIT_ID_MERCHANT;
}

void Merchant::save(ostream &out) {
    Unit::save(out);
    
    out << "#-------------------- class Merchant" << endl;
    
    itemsToSell->save(out);
    itemsBought->save(out);
}

void Merchant::load(istream &in) {
    Unit::load(in);
        
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Merchant" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    itemsToSell->load(in);
    itemsBought->load(in);
}

//------------------------------------------------------------------------------
// class Ghost
//------------------------------------------------------------------------------
Ghost::Ghost() : Unit(DEFAULT_GHOST_SHAPE, -1, -1,
                      DEFAULT_GHOST_MAX_HP, DEFAULT_GHOST_HP,
                      DEFAULT_GHOST_MAX_MP, DEFAULT_GHOST_MP,
                      DEFAULT_GHOST_ATK, DEFAULT_GHOST_DEF,
                      DEFAULT_GHOST_GOLD, DEFAULT_GHOST_EXP) {
}

Ghost::Ghost(char shape) : Unit(shape, -1, -1,
                                DEFAULT_GHOST_MAX_HP, DEFAULT_GHOST_HP,
                                DEFAULT_GHOST_MAX_MP, DEFAULT_GHOST_MP,
                                DEFAULT_GHOST_ATK, DEFAULT_GHOST_DEF,
                                DEFAULT_GHOST_GOLD, DEFAULT_GHOST_EXP) {
}

Ghost::Ghost(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
             int atk, int def, int gold, int exp)
: Unit(shape, row, col, maxHp, hp, maxMp, mp, atk, def, gold, exp) {
}

Ghost::~Ghost() {
}

bool Ghost::isGhost() {
    return true;
}

void Ghost::move(int dir) {
    if (!isBoss() && frozen) { // when ths monster has been frozen.
        return;
    }
    
    int nextRow = -1;
    int nextCol = -1;
    
    if (dir == DIR_N) {
        nextRow = row - 1;
        nextCol = col;
    }
    else if (dir == DIR_E) {
        nextRow = row;
        nextCol = col + 1;
    }
    else if (dir == DIR_S) {
        nextRow = row + 1;
        nextCol = col;
    }
    else if (dir == DIR_W) {
        nextRow = row;
        nextCol = col - 1;
    }
    else {
        return;
    }
    
    // if the next position is empty
    if (sim->board->validate(nextRow, nextCol) &&
        sim->board->getProp(nextRow, nextCol) == NULL &&
        sim->board->getUnit(nextRow, nextCol) == NULL) {
        sim->board->setUnit(row, col, NULL);
        sim->board->setUnit(nextRow, nextCol, this);
    }
    if (nextRow % 2 == 0 && nextCol % 2 == 0) {
        //sim->board->setUnit(nextRow, nextCol, NULL);
        shape = ',';
    }
    else {
        shape = DEFAULT_GHOST_SHAPE;
    }
}

void Ghost::interact(Unit *unit) {
    if (unit == NULL) {
        return;
    }
    
    decHp(unit->getAtk()); // hero attacks me(monster or boss)
    if (!isDead()) {
        unit->decHp(atk); // I(monster or boss) attacks hero
    }
}

string Ghost::getID() {
    return UNIT_ID_GHOST;
}

void Ghost::save(ostream &out) {
    Unit::save(out);
    
    out << "#-------------------- class Ghost" << endl;
}

void Ghost::load(istream &in) {
    Unit::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Monster" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}
