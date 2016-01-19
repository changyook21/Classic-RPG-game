#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "prop.h"
#include "board.h"
#include "shockwave.h"

//extern Board *sim->board;
#include "sim.h"
extern Sim *sim;

//==============================================================================
// class Shockwave
//==============================================================================

Shockwave::Shockwave() {
    waveActivated = false;
    waveStartRow = -1;
    waveStartCol = -1;
    waveMaxRange = 0;
    waveFrameInterval = 0;
    waveCurPhase = 0;
    waveCountFrames = 0;
    waveFxShape = ' ';
    
    skillNumber = 0;
}

Shockwave::Shockwave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                     int row, int col, int range, int frameInterval, char fxShape,
                     int skillNumber) {
    waveActivated = false;
    waveStartRow = row;
    waveStartCol = col;
    waveMaxRange = range;
    waveCurPhase = 1; // don't begin from the start position.
    waveFrameInterval = frameInterval;
    waveCountFrames = 0;
    waveFxShape = fxShape;
    drawn = false;
    
    this->waveUnit = waveUnit;
    this->waveItem = waveItem;
    this->waveProp = waveProp;

    this->skillNumber = skillNumber;
}

Shockwave::~Shockwave() {
}

void Shockwave::start() {
    waveActivated = true;
}

void Shockwave::stop() {
    waveActivated = false;
}

int Shockwave::getSkillNumber() {
    return skillNumber;
}

void Shockwave::setSkillNumber(int skillNumber) {
    this->skillNumber = skillNumber;
}

void Shockwave::removePrevious() {
    if (waveCurPhase > 2 || drawn) {
        int curRange = waveCurPhase - 1;
        for (int i = waveStartRow-curRange; i <= waveStartRow+curRange; i++) {
            for (int j = waveStartCol-curRange; j <= waveStartCol+curRange; j++) {
                // if the current tile is on the boundary frame.
                if (sim->board->validate(i, j) && (i == waveStartRow-curRange || i == waveStartRow+curRange ||
                                              j == waveStartCol-curRange || j == waveStartCol+curRange)) {
                    // remove the previous fx from the current tile.
                    sim->board->clearFx(i, j);
                }
            }
        }
        
        waveCurPhase++;
        
        if (waveCurPhase == waveMaxRange+1) {
            waveActivated = false;
        }
    }
}

void Shockwave::drawCurrentPhase() {
    // draw the current fx
    int curRange = waveCurPhase - 1;
    for (int i = waveStartRow-curRange; i <= waveStartRow+curRange; i++) {
        for (int j = waveStartCol-curRange; j <= waveStartCol+curRange; j++) {
            // if the current tile is on the boundary frame.
            if (sim->board->validate(i, j) && (i == waveStartRow-curRange || i == waveStartRow+curRange ||
                                          j == waveStartCol-curRange || j == waveStartCol+curRange)) {
                // remove the previous fx from the current tile.
                sim->board->setFx(i, j, waveFxShape);
                
                // call the starter object of this shockwave
                if (waveUnit != NULL) {
                    //waveUnit->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j), skillNumber);
                }
                else if (waveItem != NULL) {
                    waveItem->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j));
                }
                else if (waveProp != NULL) {
                    waveProp->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j));
                }
            }
        }
    }
    
    drawn = true;
    
    waveCountFrames = 0;
}

void Shockwave::checkCurrentPhase() {
    // draw the current fx
    int curRange = waveCurPhase - 1;
    for (int i = waveStartRow-curRange; i <= waveStartRow+curRange; i++) {
        for (int j = waveStartCol-curRange; j <= waveStartCol+curRange; j++) {
            // if the current tile is on the boundary frame.
            if (sim->board->validate(i, j) && (i == waveStartRow-curRange || i == waveStartRow+curRange ||
                                               j == waveStartCol-curRange || j == waveStartCol+curRange)) {
                // remove the previous fx from the current tile.
                sim->board->setFx(i, j, waveFxShape);
                
                // call the starter object of this shockwave
                if (waveUnit != NULL) {
                    //waveUnit->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j), skillNumber);
                }
                else if (waveItem != NULL) {
                    waveItem->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j));
                }
                else if (waveProp != NULL) {
                    waveProp->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j));
                }
            }
        }
    }
    
    drawn = true;
}

void Shockwave::print() {
    if (waveActivated) {
        if (waveCurPhase > 1 && waveCurPhase <= waveMaxRange+1) { // started to draw fx square yet
            // remove the previous frame when waveCountFrames reaches waveFrameInterval
            if (waveCountFrames >= waveFrameInterval) {
                removePrevious();
                
                if (waveCurPhase < waveMaxRange+1) {
                    drawCurrentPhase();
                }
                else { // the the starter waveItem of this shockwave should be disposed
                    if (waveItem != NULL) {
                        waveItem->dispose();
                        if (waveItem->isDisposed()) {
                            delete waveItem;
                            waveItem = NULL;
                        }
                    }
                }
            }
            else {
                checkCurrentPhase();
            }
            waveCountFrames++;
        }
        else {
            waveCurPhase++;
        }
    }
}

bool Shockwave::getWaveActivated() {
    return waveActivated;
}

Shockwave *createShockwaveBySkillID(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                                    int row, int col, int skillNumber) {
    if (skillNumber == SHOCKWAVE_HOLY_STATUE_ID) {
        return new Shockwave(waveUnit, waveItem, waveProp, row, col,
                             HOLY_STATUE_WAVE_RANGE, HOLY_STATUE_WAVE_FRAME_INTERVAL, HOLY_STATUE_WAVE_SHAPE,
                             skillNumber);
    }
    else if (skillNumber == SHOCKWAVE_ANTICROSS_ID) {
        return new AntiCross(waveUnit, waveItem, waveProp, row, col, skillNumber);
    }
    else { // if (skillNumber == SHOCKWAVE_DEFAULT_ID) {
        return new Shockwave(waveUnit, waveItem, waveProp, row, col,
                             DEFAULT_WAVE_RANGE, DEFAULTWAVE_FRAME_INTERVAL, DEFAULT_WAVE_SHAPE,
                             skillNumber);
    }
}

//==============================================================================
// class AntiCross
//==============================================================================

AntiCross::AntiCross()
    : Shockwave(NULL, NULL, NULL, -1, -1, 0, 0, '\0', 0) {
}

AntiCross::AntiCross(Unit *waveUnit, Item *waveItem, Prop *waveProp, int row, int col,
                     int skillNumber)
    : Shockwave(waveUnit, waveItem, waveProp, row, col,
                DEFAULT_ANTICROSS_RANGE, DEFAULT_ANTICROSS_FRAME_INTERVAL, DEFAULT_ANTICROSS_SHAPE,
                skillNumber) {
}

AntiCross::~AntiCross() {
}

void AntiCross::removePrevious() {
    if (waveCurPhase > 2 || drawn) {
        int curRange = waveCurPhase - 1;
        for (int i = waveStartRow-curRange; i <= waveStartRow+curRange; i++) {
            for (int j = waveStartCol-curRange; j <= waveStartCol+curRange; j++) {
                // if the current tile is on the boundary frame.
                if (sim->board->validate(i, j) &&
                    ((i > waveStartRow && j > waveStartCol) ||
                     (i < waveStartRow && j < waveStartCol) ||
                     (i < waveStartRow && j > waveStartCol) ||
                     (i > waveStartRow && j < waveStartCol))) {
                    // remove the previous fx from the current tile.
                    sim->board->clearFx(i, j);
                }
            }
        }
        
        waveCurPhase++;
        
        if (waveCurPhase == waveMaxRange+1) {
            waveActivated = false;
        }
    }
}

void AntiCross::drawCurrentPhase() {
    // draw the current fx
    int curRange = waveCurPhase - 1;
    for (int i = waveStartRow-curRange; i <= waveStartRow+curRange; i++) {
        for (int j = waveStartCol-curRange; j <= waveStartCol+curRange; j++) {
            // if the current tile is on the boundary frame.
            if (sim->board->validate(i, j) &&
                ((i > waveStartRow && j > waveStartCol)|| 
                 (i < waveStartRow && j < waveStartCol ) ||
                 (i < waveStartRow && j > waveStartCol) || 
                 (i > waveStartRow && j < waveStartCol))) {
                // remove the previous fx from the current tile.
                sim->board->setFx(i, j, waveFxShape);
                
                // call the starter object of this shockwave
                if (waveUnit != NULL) {
                    //waveUnit->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j), skillNumber);
                }
                else if (waveItem != NULL) {
                    //waveItem->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j));
                }
                else if (waveProp != NULL) {
                    waveProp->effect(sim->board->getUnit(i, j), sim->board->getItem(i, j), sim->board->getProp(i, j));
                }
            }
        }
    }
    
    drawn = true;
    
    waveCountFrames = 0;
}
