#include <math.h>
#ifndef TILE_H
#define TILE_H

class Unit;
class Item;
class Prop;

#define FX_NONE '\0'

class Tile {
protected:
public:
    char astarStep;
    
    int row;
    int col;

    char fx; // fx layer

    Unit *unit;
    Item *throwableItem;
    Item *item;
    Prop *prop;
    
    // private helper function
    void initTile(int row, int col);
    void destroyTile();
    
public:
    Tile();
    Tile(int row, int col);
    virtual ~Tile();
    
    void print();

    char getFx();
    void setFx(char fx);
    void clearFx(); // resteFx()

    Unit *getUnit();
    void setUnit(Unit *unit);

    Item *getThrowableItem();
    void setThrowableItem(Item *throwableItem);

    Item *getItem();
    void setItem(Item *item);

    Prop *getProp();
    void setProp(Prop *prop);
    
    void save(ostream &out);
    void load(istream &in);
    
    //==========================================================================
    // AStar related
    //==========================================================================
    int f;
    int g;
    int h;
    
    Tile *cameFrom;
    
    void clearAStar(); // resteFx()
    float distance(Tile *nodeGoal);
};

#endif
