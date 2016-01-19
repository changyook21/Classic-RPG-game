#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "item.h"
#include "board.h"
#include "unit.h"
#include "prop.h"
#include "a_star.h"
#include "tile.h"
#include "monster.h"

//extern Board *sim->board;
#include "sim.h"
extern Sim *sim;

//------------------------------------------------------------------------------
// class Monster
//------------------------------------------------------------------------------
Monster::Monster() : Unit(DEFAULT_MONSTER_SHAPE, -1, -1,
                          DEFAULT_MONSTER_MAX_HP, DEFAULT_MONSTER_HP,
                          DEFAULT_MONSTER_MAX_MP, DEFAULT_MONSTER_MP,
                          DEFAULT_MONSTER_ATK, DEFAULT_MONSTER_DEF,
                          DEFAULT_MONSTER_GOLD, DEFAULT_MONSTER_EXP) {
}

Monster::Monster(char shape) : Unit(shape, -1, -1,
                                    DEFAULT_MONSTER_MAX_HP, DEFAULT_MONSTER_HP,
                                    DEFAULT_MONSTER_MAX_MP, DEFAULT_MONSTER_MP,
                                    DEFAULT_MONSTER_ATK, DEFAULT_MONSTER_DEF,
                                    DEFAULT_MONSTER_GOLD, DEFAULT_MONSTER_EXP) {
}

Monster::Monster(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
                 int atk, int def, int gold, int exp)
    : Unit(shape, row, col, maxHp, hp, maxMp, mp, atk, def, gold, exp) {
}

Monster::~Monster() {
}

bool Monster::isMonster() {
    return true;
}

void Monster::move(int dir) {
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
}

void Monster::interact(Unit *unit) {
    if (unit == NULL) {
        return;
    }
    
    decHp(unit->getAtk()); // hero attacks me(monster or boss)
    if (!isDead()) {
        unit->decHp(atk); // I(monster or boss) attacks hero
    }
}

string Monster::getID() {
    return UNIT_ID_MONSTER;
}

void Monster::save(ostream &out) {
    Unit::save(out);
    
    out << "#-------------------- class Monster" << endl;
}

void Monster::load(istream &in) {
    Unit::load(in);
        
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Monster" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}

//------------------------------------------------------------------------------
// class Boss
//------------------------------------------------------------------------------
Boss::Boss() : Monster(DEFAULT_BOSS_SHAPE, -1, -1,
                       DEFAULT_BOSS_MAX_HP, DEFAULT_BOSS_HP,
                       DEFAULT_BOSS_MAX_MP, DEFAULT_BOSS_MP,
                       DEFAULT_BOSS_ATK, DEFAULT_BOSS_DEF,
                       DEFAULT_BOSS_GOLD, DEFAULT_BOSS_EXP) {
    range = DEFAULT_BOSS_RANGE;
    
//    path = false;
//    numPath = 0;
//    curPathIndex = 0;
    pathAStar = NULL;
}

Boss::Boss(char shape, int range) : Monster(shape, -1, -1,
                                            DEFAULT_BOSS_MAX_HP, DEFAULT_BOSS_HP,
                                            DEFAULT_BOSS_MAX_MP, DEFAULT_BOSS_MP,
                                            DEFAULT_BOSS_ATK, DEFAULT_BOSS_DEF,
                                            DEFAULT_BOSS_GOLD, DEFAULT_BOSS_EXP) {
    this->range = range;

//    path = false;
//    numPath = 0;
//    curPathIndex = 0;
    pathAStar = NULL;
}

Boss::~Boss() {
}

void Boss::reset() {
    Unit::reset();
    
    delete pathAStar;
    pathAStar = NULL;
}

bool Boss::isBoss() {
    return true;
}

string Boss::getID() {
    return UNIT_ID_BOSS;
}

void Boss::save(ostream &out) {
    Monster::save(out);
    
    out << "#-------------------- class Boss" << endl;

    out << "# range" << endl;
    out << range << endl;
}

void Boss::load(istream &in) {
    Monster::load(in);
        
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Boss" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
//    path = false;
//    numPath = 0;
//    curPathIndex = 0;
    pathAStar = NULL;
    
    //out << "# range" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << range << endl;
    in >> range;
    in.get(); // skip enter code.
}

void Boss::move(int dir) {
    if (died) {
        return;
    }
    
    bool cancelCurrentPath = false;
    if (pathAStar != NULL) {
        // boss follow the path left.
        if (pathAStar->size() > 1) {
            Tile *currentTile = pathAStar->popBack();
            int nextRow = currentTile->row;
            int nextCol = currentTile->col;
            // if the next position is empty
            if (sim->board->validate(nextRow, nextCol) &&
                sim->board->getProp(nextRow, nextCol) == NULL &&
                sim->board->getUnit(nextRow, nextCol) == NULL) {
                sim->board->setUnit(row, col, NULL);
                sim->board->setUnit(nextRow, nextCol, this);
            }
            else {
                pathAStar->pushBack(currentTile);
                cancelCurrentPath = true;
            }
            
            if (!cancelCurrentPath) {
                return;
            }
        }
        
        delete pathAStar;
        pathAStar = NULL;
    }
    
    AStar *aStar = new AStar();
    
    DLLContainer<Tile *> *path = aStar->findPath(row, col, sim->board->getHero()->getRow(), sim->board->getHero()->getCol());
    delete aStar;
    if (path != NULL && path->size() > 2) {
        pathAStar = path;
        path->popBack(); // boss skip boss' position.
//        while (!path->isEmpty()) {
//            Tile *currentTile = path->popBack();
//            cout << "(" << currentTile->row << ", " << currentTile->col << ")->";
//        }
//        cout << endl;
//        sim->board->print();
//        exit(1);
        return;
    }
    
    if (path != NULL) {
        delete path;
    }
        
    // if hero is adjavcent then hit him.
    for (int i = row-1; i <= row+1; i++) {
        for (int j = col-1; j <= col+1; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                sim->board->getUnit(i, j)->isHero()) {
                sim->board->getUnit(i, j)->decHp(atk); // found! attak!!!
                return;
            }
        }
    }
        
    Monster::move(dir);
}
