#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "board.h"
#include "prop.h"

//extern Board *sim->board;
#include "sim.h"
extern Sim *sim;

//------------------------------------------------------------------------------
// class Prop: the parent class of class Tree & Portal & Fountain & Bush
//------------------------------------------------------------------------------
Prop::Prop() {
    this->shape = '\0';
    
    row = -1;
    col = -1;
}

Prop::Prop(char shape) {
    this->shape = shape;

    row = -1;
    col = -1;
}

Prop::~Prop() {
}

void Prop::print() {
    cout << shape;
}

int Prop::getRow() {
    return row;
}

void Prop::setRow(int row) {
    this->row = row;
}

int Prop::getCol() {
    return col;
}

void Prop::setCol(int col) {
    this->col = col;
}

bool Prop::isClimbable() {
    // N/A
    return false;
}



bool Prop::kickout() {
    // N/A
    return false;
}

bool Prop::isTree() {
	// N/A
	return false;
}

bool Prop::isPortal() {
	// N/A
	return false;
}

bool Prop::isFount() {
	// N/A
	return false;
}

bool Prop::isDoor() {
	// N/A
	return false;
}

bool Prop::isCar() {
	return false;
}

bool Prop::isHolyStatue() {
    // N/A
    return false;
}

bool Prop::isBush() {
	// N/A
	return false;
}

void Prop::trigger(Unit *unit) {
    // N/A
}

void Prop::deactivate(Unit *unit) {
    // N/A
}

void Prop::drive(int dir) {
    // N/A
}

void Prop::effect(Unit *unit, Item *item, Prop *prop) {
    // N/A
}

void Prop::save(ostream &out) {
    out << "#-------------------- class Prop" << endl;
    
    out << "# shape" << endl;
    out << shape << endl; 

    out << "# row" << endl;
    out << row << endl; 

    out << "# col" << endl;
    out << col << endl; 
}

void Prop::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Prop" << endl;
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
}

Prop *createPropByShape(char shape) {
    if (shape == DEFAULT_TREE_SHAPE) {
        return new Tree();
    }
    else if (shape == DEFAULT_PORTAL_SHAPE) {
        return new Portal();
    }
    else if (shape == DEFAULT_FOUNTAIN_SHAPE) {
        return new Fount();
    }
	else if (shape == DEFAULT_BUSH_SHAPE) {
		return new Bush();
	}
    else if (shape == DEFAULT_CAR_SHAPE) {
        return new Car();
    }
    else if (shape == DEFAULT_HOLY_STATUE_SHAPE) {
        return new HolyStatue();
    }
    else if (shape == DEFAULT_EXIT_SHAPE) {
        return new Exit();
    }
    else if (shape == DEFAULT_WALL_SHAPE_01 ||
             shape == DEFAULT_WALL_SHAPE_02 ||
             shape == DEFAULT_WALL_SHAPE_03) {
        return new Wall(shape);
    }
	else if (shape == DEFAULT_DOOR_SHAPE) {
		return new Exit();
	}
    
    return NULL;
}

Prop *createPropByID(string propID) {
    if (propID == PROP_ID_TREE) {
        return new Tree();
    }
    else if (propID == PROP_ID_PORTAL) {
        return new Portal();
    }
    else if (propID == PROP_ID_FOUNTAIN) {
        return new Fount();
    }
    else if (propID == PROP_ID_BUSH) {
        return new Bush();
    }
    else if (propID == PROP_ID_CAR) {
        return new Car();
    }
    else if (propID == PROP_ID_HOLY_STATUE) {
        return new HolyStatue();
    }
    else if (propID == PROP_ID_EXIT) {
        return new Exit();
    }
    else if (propID == PROP_ID_WALL) {
        return new Wall();
    }
	else if (propID == PROP_ID_DOOR) {
		return new Wall();
	}
    return NULL;
}

//------------------------------------------------------------------------------
// class Tree: the child class of class Prop.
//------------------------------------------------------------------------------
Tree::Tree() : Prop(DEFAULT_TREE_SHAPE) {
}

Tree::Tree(char shape) : Prop(shape) {
}

Tree::~Tree() {
}

bool Tree::isTree() {
	return true;
}

string Tree::getID() {
    return PROP_ID_TREE;
}

void Tree::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Tree" << endl;
}

void Tree::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Tree" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}

//------------------------------------------------------------------------------
// class Portal: the child class of class Prop.
//------------------------------------------------------------------------------
Portal::Portal() : Prop(DEFAULT_PORTAL_SHAPE) {
}

Portal::Portal(char shape) : Prop(shape) {
}

Portal::~Portal() {
}

bool Portal::isClimbable() {
    return true;
}

bool Portal::isPortal() {
	return true;
}

void Portal::trigger(Unit *unit) { // virtual function
	if (unit == NULL) {
		return;
	}

	while (true) { // infinite loop
		int randRow = rand() % sim->board->getRowSize();
		int randCol = rand() % sim->board->getColSize();

		if (sim->board->getProp(randRow, randCol) == NULL &&
			sim->board->getUnit(randRow, randCol) == NULL &&
			sim->board->getItem(randRow, randCol) == NULL) {
			sim->board->setUnit(unit->getRow(), unit->getCol(), NULL);
			sim->board->setUnit(randRow, randCol, unit);
			break;
		}
	}
}

string Portal::getID() {
    return PROP_ID_PORTAL;
}

void Portal::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Portal" << endl;
}

void Portal::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Portal" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}

//------------------------------------------------------------------------------
// class Fountain: the child class of class Prop.
//------------------------------------------------------------------------------
Fount::Fount() : Prop(DEFAULT_FOUNTAIN_SHAPE) {
    hp = DEFAULT_FOUNTAIN_HP;
    mp = DEFAULT_FOUNTAIN_MP;
}

Fount::Fount(char shape, int hp, int mp) : Prop(shape) {
    this->hp = hp;
    this->mp = mp;
}

Fount::~Fount() {
}

bool Fount::isFount() {
	return true;
}

void Fount::trigger(Unit *unit) { // virtual function
    if (unit == NULL) {
        return;
    }
    
    unit->incHp(hp);
    unit->incMp(mp);
}

string Fount::getID() {
    return PROP_ID_FOUNTAIN;
}

void Fount::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Fount" << endl;
    
    out << "# hp" << endl;
    out << hp << endl; 
    
    out << "# mp" << endl;
    out << mp << endl; 
}

void Fount::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Prop" << endl;
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
// class Bush: the child class of class Prop.
//------------------------------------------------------------------------------
Bush::Bush() : Prop(DEFAULT_BUSH_SHAPE) {
    unitHidden = NULL;
}

Bush::Bush(char shape) : Prop(shape) {
    unitHidden = NULL;
}

Bush::~Bush() {
}

bool Bush::isClimbable() {
	return true;
}

bool Bush::isBush() {
	return true;
}

void Bush::trigger(Unit *unit) { // virtual function
    if (unit == NULL) {
        return;
    }
    
    if (unitHidden != NULL) {
        return;
    }
    
    sim->board->setUnit(unit->getRow(), unit->getCol(), NULL);
    unit->setRow(row);
    unit->setCol(col);
    unitHidden = unit;
}

void Bush::deactivate(Unit *unit) {
    unitHidden = NULL;
}

string Bush::getID() {
    return PROP_ID_BUSH;
}

void Bush::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Bush" << endl;
    
    //out << "# unitHidden" << endl;
    //unitHidden->save(out);
}

void Bush::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Bush" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    // don't save unitHidden
}
//------------------------------------------------------------------------------
// class Door
//------------------------------------------------------------------------------
Door::Door() : Prop(DEFAULT_DOOR_SHAPE) {
	
}

Door::Door(char shape) : Prop(shape) {
	
}

Door::~Door() {
}

bool Door::isDoor() {
	return true;
}

void Door::trigger(Unit *unit) { // virtual function
	if (unit == NULL) {
		return;
	}
}

string Door::getID() {
	return PROP_ID_DOOR;
}

void Door::save(ostream &out) {
	Prop::save(out);

	out << "#-------------------- class Bush" << endl;

	//out << "# unitHidden" << endl;
	//unitHidden->save(out);
}

void Door::load(istream &in) {
	Prop::load(in);

	char buf[MAX_LEN_BUF];

	//out << "#-------------------- class Bush" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment

								  // don't save unitHidden
}
//------------------------------------------------------------------------------
// class Car: the child class of class Prop.
//------------------------------------------------------------------------------
Car::Car() : Prop(DEFAULT_CAR_SHAPE) {
    passenger = NULL;
    prevDir = DEFAULT_CAR_DIR;
    dir = DEFAULT_CAR_DIR;
    speed = SPEED_CAR;
    visited = false;
}

Car::Car(char shape) : Prop(shape) {
    passenger = NULL;
    prevDir = DEFAULT_CAR_DIR;
    dir = DEFAULT_CAR_DIR;
    speed = SPEED_CAR;
    visited = false;
}

Car::~Car() {
}

void Car::setDir(int dir) {
    this->dir = dir;
}

bool Car::isVisited() {
    return visited;
}

void Car::resetVisited() {
    visited = false;
}





bool Car::kickout() {
    if (passenger != NULL) {
        int exitDir = (prevDir + NUM_DIRS - 1) % NUM_DIRS;
        
        for (int i = 0; i < NUM_DIRS; i++) {
            int exitRow = -1;
            int exitCol = -1;
            
            if (exitDir == DIR_N) {
                exitRow = row - 1;
                exitCol = col;
            }
            else if (exitDir == DIR_E) {
                exitRow = row;
                exitCol = col + 1;
            }
            else if (exitDir == DIR_S) {
                exitRow = row + 1;
                exitCol = col;
            }
            else { // if (exitDir == DIR_W) {
                exitRow = row;
                exitCol = col - 1;
            }        
            
            // if the exit position is empty
            if (sim->board->validate(exitRow, exitCol) &&
                sim->board->getProp(exitRow, exitCol) == NULL &&
                sim->board->getUnit(exitRow, exitCol) == NULL) {
                sim->board->setUnit(exitRow, exitCol, passenger);
                passenger = NULL;
                return true;
            }
            
            exitDir = (exitDir + 1) % NUM_DIRS;
        }        
    }
    return false;
}

bool Car::isCar() {
	return true;
}

void Car::trigger(Unit *unit) { // virtual function
    if (unit == NULL) {
        return;
    }
    
    if (passenger != NULL) {
        return;
    }

   
    passenger = unit;
}

void Car::deactivate(Unit *unit) {
    passenger = NULL;
}

void Car::drive(int dir) {
    visited = true;
    
    if (passenger != NULL) {
        if (dir == DIR_NONE) {
            if (this->dir == DIR_NONE) {
                return;
            }
        }
        else {
            if (this->dir == DIR_NONE) {
                prevDir = this->dir;
                this->dir = dir;
            }
            
        }

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
            sim->board->getUnit(nextRow, nextCol) == NULL) {
            sim->board->setProp(row, col, NULL);
            sim->board->setProp(nextRow, nextCol, this);
			
        }
		else {
			sim->board->setProp(row, col, NULL);
		}
    }
}

string Car::getID() {
    return PROP_ID_CAR;
}

void Car::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Car" << endl;
    
    //out << "# passenger" << endl;
    //passenger->save(out);
    
    out << "# prevDir" << endl;
    out << prevDir << endl; 
    
    out << "# dir" << endl;
    out << dir << endl; 

    out << "# speed" << endl;
    out << speed << endl; 
    
    out << "# visited" << endl;
    out << visited << endl; 
}

void Car::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Car" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    // don't save unitHidden
    
    //out << "# prevDir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << prevDir << endl;
    in >> prevDir;
    in.get(); // skip enter code.
    
    //out << "# dir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << dir << endl;
    in >> dir;
    in.get(); // skip enter code.

    //out << "# speed" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << speed << endl;
    in >> speed;
    in.get(); // skip enter code.
    
    //out << "# visited" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << visited << endl;
    in >> visited;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Fountain: the child class of class Prop.
//------------------------------------------------------------------------------
HolyStatue::HolyStatue() : Prop(DEFAULT_HOLY_STATUE_SHAPE) {
    initHolyStatue(DEFAULT_HOLY_STATUE_HP, DEFAULT_HOLY_STATUE_MP);
}

HolyStatue::HolyStatue(char shape, int hp, int mp) : Prop(shape) {
    initHolyStatue(hp, mp);
}

void HolyStatue::initHolyStatue(int hp, int mp) {
    this->hp = hp;
    this->mp = mp;
    interval = HOLY_STATUE_INTERVAL;
}

HolyStatue::~HolyStatue() {
}

bool HolyStatue::isHolyStatue() {
    return true;
}

void HolyStatue::start() {
    if (interval == HOLY_STATUE_INTERVAL) {
        sim->board->startWave(NULL, NULL, this,
                     row, col, SHOCKWAVE_HOLY_STATUE_ID);
    }
    
    interval--;
    if (interval <= 0) {
        interval = HOLY_STATUE_INTERVAL;
    }
}

void HolyStatue::trigger(Unit *unit) { // virtual function
}

void HolyStatue::effect(Unit *unit, Item *item, Prop *prop) {
    if (unit == NULL) {
        return;
    }
    
    unit->incHp(hp);
    unit->incMp(mp);
}

string HolyStatue::getID() {
    return PROP_ID_HOLY_STATUE;
}

void HolyStatue::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class HolyStatue" << endl;
    
    out << "# hp" << endl;
    out << hp << endl; 
    
    out << "# mp" << endl;
    out << mp << endl; 
    
    out << "# interval" << endl;
    out << interval << endl; 
}

void HolyStatue::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class HolyStatue" << endl;
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
    
    //out << "# interval" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << interval << endl;
    in >> interval;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Exit: the child class of class Prop.
//------------------------------------------------------------------------------
Exit::Exit() : Prop(DEFAULT_EXIT_SHAPE) {
}

Exit::Exit(char shape) : Prop(shape) {
}

Exit::~Exit() {
}

bool Exit::isClimbable() {
    return true;
}

bool Exit::isExit() {
    return true;
}

void Exit::trigger(Unit *unit) { // virtual function
    if (unit == NULL) {
        return;
    }
    
    sim->board->setExited(true);
}

string Exit::getID() {
    return PROP_ID_EXIT;
}

void Exit::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Exit" << endl;
}

void Exit::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Exit" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}

//------------------------------------------------------------------------------
// class Wall: the child class of class Prop.
//------------------------------------------------------------------------------
Wall::Wall() : Prop(DEFAULT_WALL_SHAPE_01) {
}

Wall::Wall(char shape) : Prop(shape) {
}

Wall::~Wall() {
}

bool Wall::isWall() {
    return true;
}

string Wall::getID() {
    return PROP_ID_WALL;
}

void Wall::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Wall" << endl;
}

void Wall::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Wall" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}

