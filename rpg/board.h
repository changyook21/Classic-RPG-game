#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Tile;
class Unit;
class Hero;
class Prop;
class Monster;
class Boss;
class Ghost;
class Merchant;
class Shockwave;

class Board {
//protected:
public:
    int rowSize;
    int colSize;
	int openList;
	int closedList;

	int dir;
    Tile ***board;

    Hero *hero;
	//Prop *car;
    
    Monster **mons;
    int maxNumMons;
    int numMons;
	
	Ghost **ghost;
	int maxNumGhost;
	int numGhost;

	Boss **boss;
	int maxNumBoss;
	int numBoss;

	Merchant **merchant;
	int maxNumMerchant;
	int numMerchant;
    
    bool exited;
	bool hasTorch;
    bool dayAndNight;
    int rangeNight;
    
    // for shockwave
    Shockwave **shockwaves;
    int maxNumShockwaves;
    int numShockwaves;
    
    // private helper functions.
    void initFx();

    void destroyBoard();
    void destroyFx();

public:
    Board();
    void initBoard();
    bool loadLevel(istream &in);
    virtual ~Board();
    
    void nextShockWave();
    void print();
    
    void clearFx(int row, int col);
    void setFx(int row, int col, char fx);
    void startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                   int row, int col, int skillNumber);
    void startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                   int row, int col, int range, int frameInterval, char fxShape,
                   int skillNumber);

    int getRowSize();
    int getColSize();
    
    Tile *getTile(int row, int col);
    
	//================================================================================================
	//A* header 
	//================================================================================================
	
	Tile *start;
	Tile *goal;
	bool foundGoal;
	//===============================================================================================
	//===============================================================================================
    bool validate(int row, int col);
        
    Hero *getHero();
    
    Unit *getUnit(int row, int col);
    void setUnit(int row, int col, Unit *unit);

    Item *getThrowableItem(int row, int col);
    void setThrowableItem(int row, int col, Item *throwableItem);

    Item *getItem(int row, int col);
    void setItem(int row, int col, Item *item);

    Prop *getProp(int row, int col);
    void setProp(int row, int col, Prop *prop);

    bool isExited();
    void setExited(bool exited);
    
    bool getDayAndNight();
    void setDayAndNight(bool dayAndNight);
    void toggleDayAndNight();
	void activateTorch();

    void moveDrivableProps(int dir);
    void moveMons();
	void moveGhost();
	void moveBoss();
	void moveMerchant();
    void triggerAutoProps();
    void moveThrowableItems();
    
    void save(ostream &out);
    void load(istream &in);
};

#endif
