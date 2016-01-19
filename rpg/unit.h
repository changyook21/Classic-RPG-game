#ifndef UNIT_H
#define UNIT_H

#include <string>

using namespace std;

//------------------------------------------------------------------------------
// class Unit
//------------------------------------------------------------------------------
class Item;
class Board;
class Inventory;
class Backpack;
class Paperdoll;

class Unit {
protected:
	char shape;

	int row;
	int col;

    int maxHp;
	int hp;
	int maxMp;
	int mp;
	int atk;
	int def;
	int gold;
	int exp;

	bool died;
	bool frozen;

	Unit *unitEngaged;

public:
	Unit();
	Unit(char shape);
	Unit(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
		int atk, int def, int gold, int exp);

	virtual ~Unit();

    virtual void reset();
    
	void print();
	virtual void printStat();

	int getRow();
	void setRow(int row);

	int getCol();
	void setCol(int col);

	int getHp();
	void incHp(int hpToInc);
	void decHp(int hpToDec);

	int getMp();
	void incMp(int mpToInc);
	void decMp(int mpToDec);

	int getAtk();
	void incAtk(int atkToInc);
	void decAtk(int atkToDec);

	int getDef();
	void incDef(int defToInc);
	void decDef(int defToDec);

	int getGold();
	void incGold(int goldToInc);
	void decGold(int goldToDec);

	int getExp();
	void incExp(int expToInc);

	bool isDead();
    void setDied(bool died);
    
	bool getFrozen();
	void setFrozen(bool frozen);

	Unit *getUnitEngaged();
	void setUnitEngaged(Unit *unitEngaged);

	virtual bool isHero(); // virtual function
	virtual bool isMonster(); // virtual function
	virtual bool isGhost(); // virtual function
	virtual bool isBoss(); // virtual function
	virtual bool isMerchant(); // virtual function

    virtual void showItemsListToSell();
    virtual Item *removeItemByIndex(int index);
    virtual bool receiveItem(Item *item);
    
    virtual bool equip(Item *item);
    virtual bool unequip(int bodyPartID);
    
	virtual void move(int dir) = 0; // pure virtual function
    virtual void move(int dir, bool bounceKeyPressed); // virtual function
	virtual void interact(Unit *unit) = 0; // pure virtual function
    
    virtual string getID() = 0; // pure virtual function
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Unit *createUnitByShape(char shape);
Unit *createUnitByID(string unitID);

//------------------------------------------------------------------------------
// class Hero
//------------------------------------------------------------------------------
class Hero : public Unit {
protected:
    Inventory *slots;
    Backpack *backpack;
    Paperdoll *paperdoll;
    
	bool key;
	bool bounce;
    int bounceRange;

    int dir;

    // private helper functions
    void initHero();
    void destroyHero();
    
public:
	Hero();
	Hero(char shape);

	virtual ~Hero();

	virtual void printStat();

	virtual bool isHero(); // override
    
    virtual void showItemsListToSell();
    virtual Item *removeItemByIndex(int index);
    virtual bool receiveItem(Item *item);

    bool moveItemFromSlotsToBackpack(int indexItemOfSlots);
    bool moveItemFromBackpackToSlots(int indexItemOfBackpack, int indexItemOfSlots);

    virtual bool equip(Item *item);
    virtual bool unequip(int bodyPartID);

    void shoot();
    
	virtual void move(int dir); // override
    virtual void move(int dir, bool bounceKeyPressed); // virtual function

	virtual void interact(Unit *unit); // override
    
    void useItem(int index);
    
    void kickout();
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Merchant
//------------------------------------------------------------------------------
class Merchant : public Unit {
protected:
    Backpack *itemsToSell;
    Backpack *itemsBought;

public:
	Merchant();
	Merchant(char shape);

	virtual ~Merchant();

	virtual bool isMerchant(); // virtual function

	virtual void move(int dir); // override
	virtual void interact(Unit *unit); // override

    virtual void buy(Unit *unit);
    virtual void sell(Unit *unit);
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Ghost
//------------------------------------------------------------------------------
class Ghost : public Unit {
protected:
public:
	Ghost();
	Ghost(char shape);
	Ghost(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
		int atk, int def, int gold, int exp);

	virtual ~Ghost();

	virtual bool isGhost(); // virtual function

	virtual void move(int dir); // override
	virtual void interact(Unit *unit); // override

	virtual string getID();

	virtual void save(ostream &out);
	virtual void load(istream &in);
};

#endif
