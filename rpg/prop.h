#ifndef PROP_H
#define PROP_H

class Unit;

//------------------------------------------------------------------------------
// class Prop: the parent class of class Tree & Portal
//------------------------------------------------------------------------------
class Prop {
protected:
    char shape;

    int row;
    int col;
    
public:
    Prop();
    Prop(char shape);
    
    virtual ~Prop();
    
    void print();
    
    int getRow();
    void setRow(int row);
    
    int getCol();
    void setCol(int col);
    
    virtual bool isClimbable(); // virtual function

    virtual bool kickout();
    
	virtual bool isTree(); // virtual function
	virtual bool isPortal(); // virtual function
	virtual bool isBush(); // virtual function
	virtual bool isFount(); // virtual function
	virtual bool isCar(); // virtual function
	virtual bool isDoor();
    virtual bool isHolyStatue(); // virtual function

    virtual void trigger(Unit *unit); // virtual function
    virtual void effect(Unit *unit, Item *item, Prop *prop);

    virtual void deactivate(Unit *unit); // virtual function

    virtual void drive(int dir); // virtual function
    
    virtual string getID() = 0; // pure virtual function

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

Prop *createPropByShape(char shape);
Prop *createPropByID(string propID);

//------------------------------------------------------------------------------
// class Tree: the child class of class Prop.
//------------------------------------------------------------------------------
class Tree : public Prop { // extents class Prop.
protected:
public:
    Tree();
    Tree(char shape);
    
    virtual ~Tree();

    virtual bool isTree(); // virtual function
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Portal: the child class of class Prop.
//------------------------------------------------------------------------------
class Portal : public Prop { // extents class Prop.
protected:
public:
	Portal();
	Portal(char shape);

    virtual ~Portal();

    virtual bool isClimbable(); // virtual function
	virtual bool isPortal(); // virtual function
    
    virtual void trigger(Unit *unit); // virtual function

    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Fount: the child class of class Prop.
//------------------------------------------------------------------------------
class Fount : public Prop { // extents class Prop.
protected:
    int hp;
    int mp;
    
public:
	Fount();
	Fount(char shape, int hp, int mp);
    
    virtual ~Fount();

    virtual bool isFount(); // virtual function
    
    virtual void trigger(Unit *unit); // virtual function
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class bush: the child class of class Prop.
//------------------------------------------------------------------------------
class Bush : public Prop { // extents class Prop.
protected:
    Unit *unitHidden;

public:
	Bush();
	
	Bush(char shape);

	virtual ~Bush();
	virtual bool isClimbable(); // virtual function
	virtual bool isBush(); // virtual function

    virtual void trigger(Unit *unit); // virtual function
    virtual void deactivate(Unit *unit); // virtual function
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Door
//------------------------------------------------------------------------------
class Door : public Prop { // extents class Prop.
protected:
	Unit *unitHidden;

public:
	Door();

	Door(char shape);

	virtual ~Door();
	
	virtual bool isDoor(); // virtual function

	virtual void trigger(Unit *unit); // virtual function
	

	virtual string getID();

	virtual void save(ostream &out);
	virtual void load(istream &in);
};
//------------------------------------------------------------------------------
// class car: the child class of class Prop.
//------------------------------------------------------------------------------
class Car : public Prop { // extents class Prop.
protected:
    Unit *passenger;
    int prevDir;
    int dir;
    int speed;
    bool visited;
    
public:
	Car();

	Car(char shape);

	virtual ~Car();
    
    void setDir(int dir);
    
    bool isVisited();
    void resetVisited();
    


    virtual bool kickout();

	virtual bool isCar(); // virtual function

    virtual void trigger(Unit *unit); // virtual function
    virtual void deactivate(Unit *unit); // virtual function
    
    virtual void drive(int dir); // virtual function
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class HolyStatue: the child class of class Prop.
//------------------------------------------------------------------------------
class HolyStatue : public Prop { // extents class Prop.
protected:
    int hp;
    int mp;
    int interval;
    
    // private helper functions.
    void initHolyStatue(int hp, int mp);
    
public:
    HolyStatue();
    HolyStatue(char shape, int hp, int mp);
    
    virtual ~HolyStatue();
    
    virtual bool isHolyStatue(); // virtual function
    
    void start();
    
    virtual void trigger(Unit *unit); // virtual function
    virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Exit
//------------------------------------------------------------------------------
class Exit : public Prop { // extents class Prop.
protected:
public:
    Exit();
    Exit(char shape);
    
    virtual ~Exit();
    
    virtual bool isClimbable(); // virtual function
    virtual bool isExit(); // virtual function
    
    virtual void trigger(Unit *unit); // virtual function
    
    virtual string getID();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

//------------------------------------------------------------------------------
// class Wall
//------------------------------------------------------------------------------
class Wall : public Prop { // extents class Prop.
protected:
public:
    Wall();
    Wall(char shape);
    
    virtual ~Wall();
    
    virtual bool isWall(); // virtual function
        
    virtual string getID();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
