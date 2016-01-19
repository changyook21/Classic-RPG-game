#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Unit;
class Prop;

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
class Item {
protected:
    char shape;
    
    string name;
    int price;
    
    bool disposed;
    bool moved;
    bool disposable;

    int row;
    int col;
    
public:
    Item();
    Item(const Item &other);
    Item(char shape, string name, int price, bool disposable);
    
    virtual ~Item();
    
    virtual void print() const;
    virtual void printFullSpec() const;

    int getRow();
    void setRow(int row);
    
    int getCol();
    void setCol(int col);
    
    char getShape() const;
    int getPrice() const;
    
    virtual bool isConsumable() const;
    virtual bool isEquippable() const;
    
	virtual bool isPotion() const;
	virtual bool isExpotion() const;
	
    virtual bool isArmor() const;
    virtual bool isWeapon() const;
	virtual bool isBow() const;
    
    virtual bool isBounceshoe() const;
	virtual bool isKey() const;
	virtual bool isBomb() const;
	virtual bool isTorch() const;

    bool isDisposed() const;
    bool isMoved() const;
    void dispose();
    
    //--------------------------------------------------------------------------
    // only throwable items use functions below.
    //--------------------------------------------------------------------------
    virtual bool isVisited() const;
    virtual void resetVisited();
    virtual void fly(); // virtual function
    
    virtual bool isThrowableItem() const; // virtual function
    virtual bool isArrow() const; // virtual function
    //--------------------------------------------------------------------------
    // only throwable items use functions above.
    //--------------------------------------------------------------------------

    virtual string getID() const = 0;

    virtual bool use(Unit *unit) = 0;
    virtual Item *clone() const = 0;
    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

Item *createRandomItem();
Item *createItemByShape(char shape);
Item *createItemByID(string itemID);

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
class ConsumableItem : public Item {
protected:
public:
    ConsumableItem();
    ConsumableItem(const ConsumableItem &other);
    ConsumableItem(char shape, string name, int price, bool disposable);
    
    virtual ~ConsumableItem();

    virtual void printFullSpec() const;

    virtual bool isConsumable() const; // virtual function
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class EquippableItem
//------------------------------------------------------------------------------
class EquippableItem : public Item {
protected:
    int durability;
    
public:
    EquippableItem();
    EquippableItem(const EquippableItem &other);
    EquippableItem(char shape, string name, int price, bool disposable, int durability);

    virtual ~EquippableItem();
    
    virtual void printFullSpec() const;

    virtual bool isEquippable() const; // virtual function
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

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
class Potion : public ConsumableItem {
protected:
    int hp;
    int mp;
    
public:
    Potion();
    Potion(const Potion &other);
    Potion(char shape, string name, int price, bool disposable, int hp, int mp);
    
    virtual ~Potion();

    virtual void printFullSpec() const;

	virtual bool isPotion() const; // virtual function
    virtual string getID() const;
    virtual bool use(Unit *unit);
    
    virtual Item *clone() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Arrow
//------------------------------------------------------------------------------
class Arrow : public ConsumableItem {
protected:
    int dir;
    int atk;
    
    int speed;
    bool visited;
    
public:
    Arrow();
    Arrow(const Arrow &other);
    Arrow(char shape);
    Arrow(int dir, int atk);
    
    virtual ~Arrow();
    
    virtual void print() const;
    virtual void printFullSpec() const;
    
    virtual bool isVisited() const;
    virtual void resetVisited();
    virtual void fly(); // virtual function
    
    virtual bool isThrowableItem() const; // virtual function
    virtual bool isArrow() const; // virtual function
    
    virtual string getID() const;
    virtual bool use(Unit *unit);
    
    virtual Item *clone() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Expotion
//------------------------------------------------------------------------------
class Expotion : public ConsumableItem {
protected:
	int exp;
	
public:
	Expotion();
    Expotion(const Expotion &other);
	Expotion(char shape, string name, int price, bool disposable, int exp);

	virtual ~Expotion();
	
    virtual void printFullSpec() const;

	virtual bool isExpotion() const; // virtual function
    virtual string getID() const;
	virtual bool use(Unit *unit);
    
    virtual Item *clone() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Armor
//------------------------------------------------------------------------------
class Armor : public EquippableItem {
protected:
    int def;
    int bodyPartID;
    
public:
    Armor();
    Armor(const Armor &other);
    Armor(char shape, string name, int price, bool disposable, int durability, int def, int bodyPartID);
    
    virtual ~Armor();
    
    virtual void printFullSpec() const;

    int getDef();
    int getBodyPartID();
    
    bool isArmor() const;
    virtual string getID() const;
    virtual bool use(Unit *unit);
    
    virtual Item *clone() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

Armor *createRandomArmor();
Armor *createRandomArmor(char shapeToCreate);
Armor *createRandomArmorByShape(char shape);
bool isArmor(char shape);

//------------------------------------------------------------------------------
// class Weapon
//------------------------------------------------------------------------------
class Weapon : public EquippableItem {
protected:
    int atk;
    int numHands;
    
public:
    Weapon();
    Weapon(const Weapon &other);
    Weapon(char shape, string name, int price, bool disposable, int durability, int atk, int numHands);
    
    virtual ~Weapon();
    
    virtual void printFullSpec() const;

    int getAtk();
    int getNumHands();
    
    bool isWeapon() const;
    bool isBow() const;

    virtual string getID() const;
    virtual bool use(Unit *unit);
    
    virtual Item *clone() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

Weapon *createRandomWeapon();
Weapon *createRandomWeapon(char shapeToCreate);
Weapon *createRandomWeaponByShape(char shape);
bool isWeapon(char shape);

/*
//------------------------------------------------------------------------------
// class Bow
//------------------------------------------------------------------------------
class Bow : public EquippableItem {
protected:
	int atk;
	int numHands;

public:
	Bow();
	Bow(const Bow &other);
	Bow(char shape, string name, int price, int durability, int atk, int numHands);

	virtual ~Bow();

	virtual void printFullSpec() const;

	int getAtk();
	int getNumHands();

	virtual bool isBow() const;
	virtual string getID() const;
	virtual bool use(Unit *unit);

	virtual Item *clone() const;

	virtual void save(ostream &out) const;
	virtual void load(istream &in);
};
*/


//------------------------------------------------------------------------------
// class Bounceshoe
//------------------------------------------------------------------------------
class Bounceshoe : public Armor {
protected:
    int range;
    
public:
	Bounceshoe();
    Bounceshoe(const Bounceshoe &other);
	Bounceshoe(char shape, string name, int price, bool disposable, int durability,
               int def, int bodyPartID, int range);

	virtual ~Bounceshoe();

    virtual void printFullSpec() const;

    int getRange() const;
    
	virtual bool isBounceshoe() const; // virtual function
    virtual string getID() const;
	virtual bool use(Unit *unit);
    
    virtual Item *clone() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Key
//------------------------------------------------------------------------------
class Key : public ConsumableItem {
protected:
	
public:
	Key();
	Key(const Key &other);
	Key(char shape, string name, int price, bool disposable, int hp, int mp);

	virtual ~Key();

	virtual void printFullSpec() const;

	virtual bool isKey() const; // virtual function
	virtual string getID() const;
	virtual bool use(Unit *unit);

	virtual Item *clone() const;

	virtual void save(ostream &out) const;
	virtual void load(istream &in);
};
//------------------------------------------------------------------------------
// class Bomb
//------------------------------------------------------------------------------
class Bomb : public ConsumableItem {
protected:
    int range;
    int atk;
    
public:
    Bomb();
    Bomb(const Bomb &other);
    Bomb(char shape, string name, int price, bool disposable, int range, int atk);
    
    virtual ~Bomb();
    
    virtual void printFullSpec();
    
    void print(ostream &out);

	virtual bool isBomb() const; // virtual function
    virtual string getID() const;
    
    virtual bool use(Unit *unit);
    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual Item *clone() const;
	virtual void save(ostream &out) const;
	virtual void load(istream &in);
};
//------------------------------------------------------------------------------
// class Torch
//------------------------------------------------------------------------------
class Torch : public ConsumableItem {
protected:

public:
	Torch();
	Torch(const Torch &other);
	Torch(char shape, string name, int price, bool disposable, int hp, int mp);

	virtual ~Torch();

	virtual void printFullSpec() const;

	virtual bool isTorch() const; // virtual function
	virtual string getID() const;
	virtual bool use(Unit *unit);

	virtual Item *clone() const;

	virtual void save(ostream &out) const;
	virtual void load(istream &in);
};

#endif
