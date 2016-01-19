#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "monster.h"
#include "event.h"
#include "eventqueue.h"
#include "board.h"
#include "tile.h"
#include "item.h"

#include "sim.h"
extern Sim *sim;

Event::Event() {
    time = 0;
}

Event::Event(int time) {
    this->time = time;
}

Event::~Event() {
}

void Event::print() {
    cout << "time: " << time;
}

//==============================================================================
// Monster Respawn
//==============================================================================
MonRespawnEvent::MonRespawnEvent() : Event() {
    mon = NULL;
}

MonRespawnEvent::MonRespawnEvent(Monster *mon) : Event() {
    time = sim->time + rand() % MON_RESPAWN_EVENT_BASE_DURATION_DIFF + MON_RESPAWN_EVENT_BASE_DURATION_MIN;
    cout << "sim->time: " << sim->time << endl;
    cout << "FPS: " << FPS << endl;
    cout << "time: " << time << endl;
    //exit(1);
    this->mon = mon;
}

MonRespawnEvent::MonRespawnEvent(int time, Monster *mon) : Event(time) {
    this->mon = mon;
}

MonRespawnEvent::~MonRespawnEvent() {
}

void MonRespawnEvent::trigger() {
    if (mon == NULL) {
        delete this;
    }
    
    while (true) { // infinite loop
        int randRow = rand() % sim->board->getRowSize();
        int randCol = rand() % sim->board->getColSize();
        
        if (sim->board->getProp(randRow, randCol) == NULL &&
            sim->board->getUnit(randRow, randCol) == NULL &&
            sim->board->getItem(randRow, randCol) == NULL) {
            sim->board->setUnit(randRow, randCol, mon);
            break;
        }
    }
    mon->reset(); // reset died/hp/mp/...

    delete this;
}

//==============================================================================
// Boss Respawn
//==============================================================================
BossRespawnEvent::BossRespawnEvent() : Event() {
	boss = NULL;
}

BossRespawnEvent::BossRespawnEvent(Boss *boss) : Event() {
	time = sim->time + rand() % MON_RESPAWN_EVENT_BASE_DURATION_DIFF + MON_RESPAWN_EVENT_BASE_DURATION_MIN;
//	cout << "sim->time: " << sim->time << endl;
//	cout << "FPS: " << FPS << endl;
//	cout << "time: " << time << endl;
//    cout << "boss: row=" << boss->getRow() << " col=" << boss->getCol() << endl;
//	exit(1);
	this->boss = boss;
}

BossRespawnEvent::BossRespawnEvent(int time, Boss *boss) : Event(time) {
	this->boss = boss;
}

BossRespawnEvent::~BossRespawnEvent() {
}

void BossRespawnEvent::trigger() {
	if (boss == NULL) {
		delete this;
	}
    
	while (true) { // infinite loop
		int randRow = rand() % sim->board->getRowSize();
		int randCol = rand() % sim->board->getColSize();

		if (sim->board->getProp(randRow, randCol) == NULL &&
			sim->board->getUnit(randRow, randCol) == NULL &&
			sim->board->getItem(randRow, randCol) == NULL) {
			sim->board->setUnit(randRow, randCol, boss);
			break;
		}
	}
	boss->reset();

	delete this;
}

//==============================================================================
// Ghost Respawn
//==============================================================================
GhostRespawnEvent::GhostRespawnEvent() : Event() {
	ghost = NULL;
}

GhostRespawnEvent::GhostRespawnEvent(Ghost *ghost) : Event() {
	time = sim->time + rand() % MON_RESPAWN_EVENT_BASE_DURATION_DIFF + MON_RESPAWN_EVENT_BASE_DURATION_MIN;
	cout << "sim->time: " << sim->time << endl;
	cout << "FPS: " << FPS << endl;
	cout << "time: " << time << endl;
	//exit(1);
	this->ghost = ghost;
}

GhostRespawnEvent::GhostRespawnEvent(int time, Ghost *ghost) : Event(time) {
	this->ghost = ghost;
}

GhostRespawnEvent::~GhostRespawnEvent() {
}

void GhostRespawnEvent::trigger() {
	if (ghost == NULL) {
		delete this;
	}

	while (true) { // infinite loop
		int randRow = rand() % sim->board->getRowSize();
		int randCol = rand() % sim->board->getColSize();

		if (sim->board->getProp(randRow, randCol) == NULL &&
			sim->board->getUnit(randRow, randCol) == NULL &&
			sim->board->getItem(randRow, randCol) == NULL) {
			sim->board->setUnit(randRow, randCol, ghost);
			break;
		}
	}
	ghost->reset();

	delete this;
}

//==============================================================================
// Day and Night Event
//==============================================================================

DayNight::DayNight() : Event() {
	time = sim->time + DAY_AND_NIGHT_EVENT_INTERVAL;
    interval = DAY_AND_NIGHT_EVENT_INTERVAL;
}

DayNight::DayNight(int time, int interval) : Event(time) {
    this->interval = interval;
}

DayNight::~DayNight() {
}

void DayNight::trigger() {
    sim->board->toggleDayAndNight();
    
    time = sim->time + interval;
    sim->eventQueue->enqueue(this);
}
//==============================================================================
// Time Bomb
//==============================================================================
TimeBomb::TimeBomb() : Event() {
	bomb = NULL;
	row = sim->board->hero->getRow();
	col = sim->board->hero->getCol();
	range = DEFAULT_BOMB_RANGE;

	time = sim->time + rand() % MON_RESPAWN_EVENT_BASE_DURATION_DIFF + MON_RESPAWN_EVENT_BASE_DURATION_MIN;
}

TimeBomb::TimeBomb(Item *bomb) : Event(time) {
	this->bomb = bomb;
}

TimeBomb::TimeBomb(int time, Item *bomb) : Event(time) {
	this->bomb = bomb;
}

TimeBomb::~TimeBomb() {
}

void TimeBomb::trigger() {
	if (bomb == NULL) {
		delete this;
	}
	
	sim->board->startWave(NULL, bomb, NULL, row , col, range, BOMB_WAVE_FRAME_INTERVAL, BOMB_WAVE_SHAPE, 0);

	
}