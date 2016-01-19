#ifndef MONSTER_H
#define MONSTER_H

class Unit;
class Item;
class Tile;
class Board;
class Inventory;
class Backpack;
class Paperdoll;
#include "dllcontainer.h"

//------------------------------------------------------------------------------
// class Monster
//------------------------------------------------------------------------------
class Monster : public Unit {
protected:
public:
	Monster();
	Monster(char shape);
	Monster(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
		int atk, int def, int gold, int exp);

	virtual ~Monster();

	virtual bool isMonster(); // virtual function

	virtual void move(int dir); // override
	virtual void interact(Unit *unit); // override
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Boss
//------------------------------------------------------------------------------
class Boss : public Monster {
protected:
	int range;
    
//    int rowPath[BOSS_MAX_LEN_PATH];
//    int colPath[BOSS_MAX_LEN_PATH];
//    
//    int numPath;
//    int curPathIndex;
//    bool path;
    DLLContainer<Tile *> *pathAStar;

	// private helper function for move()
	bool isFrontEmpty(int curRow, int curCol, int curDir);
	void proceed(int curRow, int curCol, int curDir, int *resultRow, int *resultCol);
	int turnRight(int curDir);
	int turnLeft(int curDir);

public:
	Boss();
	Boss(char shape, int range);

	virtual ~Boss();

    virtual void reset();

	virtual bool isBoss(); // virtual function

	virtual void move(int dir); // override
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
