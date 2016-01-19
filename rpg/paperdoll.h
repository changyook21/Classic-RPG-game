#ifndef PAPERDOLL_H
#define PAPERDOLL_H

#include "main.h"
#include "item.h"
#include "unit.h"

class Paperdoll {
protected:
    Armor *head;
    Armor *chest;
    Armor *gloves;
    Armor *back;
    Armor *pants;
    Armor *boots;
    Weapon *rightHand;
    Weapon *leftHand;
    
public:
    Paperdoll();
    Paperdoll(Paperdoll &other);
    
    bool equip(Item *item, Unit *unit);
    Item *unequip(int bodyPartNo, Unit *unit);
    
    void print() const;
    
    Weapon *getRightHand() const;
    Weapon *getLeftHand() const;
    
    virtual void save(ostream &out) const;
    virtual void load(istream &in);
};

#endif
