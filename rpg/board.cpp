#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>
using namespace std;

#include "main.h"
#include "unit.h"
#include "monster.h"
#include "item.h"
#include "prop.h"
#include "tile.h"
#include "shockwave.h"
#include "testcases.h"
#include "board.h"

#include "event.h"
#include "eventqueue.h"

#include "sim.h"
extern Sim *sim;

Board::Board() {
}

void Board::initBoard() {
	rowSize = ROW_SIZE;
	colSize = COL_SIZE;

	foundGoal = false;

	board = new Tile **[rowSize];

	for (int i = 0; i < rowSize; i++) {
		board[i] = new Tile *[colSize];
	}

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			board[i][j] = new Tile(i, j);
		}
	}

    initFx();
    exited = false;
    dayAndNight = DAY;
	hasTorch = false;
    rangeNight = DAY_AND_NIGHT_EVENT_RANGE_NIGHT;
#ifndef TURN_OFF_DAY_AND_NIGHT
    sim->eventQueue->enqueue(new DayNight());
#endif

#ifdef TEST_MODE
    int countMonster = 0;
    int countBoss = 0;
    int countMerchant = 0;
	int countGhost = 0;
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            cout << TEST_BOARD[i][j];
            board[i][j] = new Tile(i, j);
            
            Unit *unit = createUnitByShape(TEST_BOARD[i][j]);
            if (unit != NULL) {
                setUnit(i, j, unit);
                
                if (unit->isHero()) {
                    hero = (Hero *)unit;
                }
                else if (unit->isBoss()) {
                    countBoss++;
                }
                else if (unit->isMonster()) {
                    countMonster++;
                }
                else if (unit->isMerchant()) {
                    countMerchant++;
                }
            }
            
            Item *item = createItemByShape(TEST_BOARD[i][j]);
            if (item != NULL) {
                setItem(i, j, item);
            }

            Prop *prop = createPropByShape(TEST_BOARD[i][j]);
            if (prop != NULL) {
                setProp(i, j, prop);
            }
        }
        cout << endl;
    }
    
    // create monsters
    mons = new Monster *[countMonster];
    maxNumMons = countMonster;
    numMons = 0;

	ghost = new Ghost *[countGhost];
	maxNumGhost = countGhost;
	numGhost = 0;
    
    boss = new Boss *[countBoss];
    maxNumBoss = countBoss;
    numBoss = 0;
    
    merchant = new Merchant *[countMerchant];
    maxNumMerchant = countMerchant;
    numMerchant = 0;

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            Unit *curUnit = board[i][j]->getUnit();
            if (curUnit != NULL) {
                if (curUnit->isBoss()) {
                    boss[numBoss] = (Boss *)curUnit;
                    numBoss++;
                }
                else if (curUnit->isMonster()) {
                    mons[numMons] = (Monster *)curUnit;
                    numMons++;
                }
				else if (curUnit->isGhost()) {
					ghost[numGhost] = (Ghost *)curUnit;
					numGhost++;
				}
                else if (curUnit->isMerchant()) {
                    merchant[numMerchant] = (Merchant *)curUnit;
                    numMerchant++;
                }
            }
        }
    }
#endif
    
#ifndef TEST_MODE
    hero = new Hero();
    setUnit(ROW_SIZE/2, COL_SIZE/2, hero);

	// create trees
	for (int i = 0; i < MAX_NUM_TREES; i++) {
		// put one random tree
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
                setProp(randRow, randCol, new Tree());
				break;
			}
		}
	}

	// create portals
	for (int i = 0; i < MAX_NUM_PORTALS; i++) {
		// put one random portal
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
                setProp(randRow, randCol, new Portal());
				break;
			}
		}
	}
	// create fountains
	for (int i = 0; i < MAX_NUM_FOUNTAINS; i++) {
		// put one random fountain
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
                setProp(randRow, randCol, new Fount());
				break;
			}
		}
	}
	// create bushes
	for (int i = 0; i < MAX_NUM_BUSHES; i++) {
		// put one random bushes
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
                setProp(randRow, randCol, new Bush());
				break;
			}
		}
	}
	// create doors
	for (int i = 0; i < MAX_NUM_DOORS; i++) {
		// put one random doors
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				setProp(randRow, randCol, new Door());
				break;
			}
		}
	}
	// create cars
	for (int i = 0; i < MAX_NUM_CARS; i++) {
		// put one random cars
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				setProp(randRow, randCol, new Car());
				break;
			}
		}
	}
    
	// create potions
	for (int i = 0; i < MAX_NUM_POTIONS; i++) {
		// put one random potiobn
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				Potion *potion = new Potion();
				board[randRow][randCol]->setItem(potion);
				break;
			}
		}
	}

    // create fountains
    for (int i = 0; i < MAX_NUM_HOLY_STATUES; i++) {
        // put one random fountain
        while (true) { // infinite loop
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                HolyStatue *holyStatue = new HolyStatue();
                setProp(randRow, randCol, holyStatue);
                holyStatue->start();
                break;
            }
        }
    }

    // create exits
    for (int i = 0; i < MAX_NUM_EXITS; i++) {
        // put one random fountain
        while (true) { // infinite loop
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                setProp(randRow, randCol, new Exit());
                break;
            }
        }
    }

	// create expotions
	for (int i = 0; i < MAX_NUM_EXPOTION; i++) {
		// put one random expotion
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				board[randRow][randCol]->setItem(new Expotion());
				break;
			}
		}
	}
    
	// create Bounceshoe
	for (int i = 0; i < MAX_NUM_BOUNCESHOE; i++) {
		// put one random Bounceshoe
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				board[randRow][randCol]->setItem(new Bounceshoe());
				break;
			}
		}
	}
    
	// create Key
	for (int i = 0; i < MAX_NUM_KEY; i++) {
		// put one random Key
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				board[randRow][randCol]->setItem(new Key());
				break;
			}
		}
	}

    // create Bomb
    for (int i = 0; i < MAX_NUM_BOMBS; i++) {
        // put one random Bomb
        while (true) { // infinite loop
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(new Bomb());
                break;
            }
        }
    }
	// create Torch
	for (int i = 0; i < MAX_NUM_TORCH; i++) {
		// put one random Torch
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				board[randRow][randCol]->setItem(new Torch());
				break;
			}
		}
	}
    // create monsters
	mons = new Monster *[MAX_NUM_MONSTERS];
	maxNumMons = MAX_NUM_MONSTERS;
	numMons = 0;
	for (int i = 0; i < MAX_NUM_MONSTERS; i++) {
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				mons[i] = new Monster();
				setUnit(randRow, randCol, mons[i]);
				break;
			}
		}
		numMons++;
	}
    
	// create ghosts
	ghost = new Ghost *[MAX_NUM_GHOSTS];
	maxNumGhost = MAX_NUM_GHOSTS;
	numGhost = 0;
	for (int i = 0; i < MAX_NUM_GHOSTS; i++) {
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				ghost[i] = new Ghost();
				setUnit(randRow, randCol, ghost[i]);
				break;
			}
		}
		numGhost++;
	}

	// create boss
	boss = new Boss *[MAX_NUM_BOSS];
	maxNumBoss = MAX_NUM_BOSS;
	numBoss = 0;
	for (int i = 0; i < MAX_NUM_BOSS; i++) {
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				boss[i] = new Boss();
				setUnit(randRow, randCol, boss[i]);
				break;
			}
		}
		numBoss++;
    }

	//create Merchant
	merchant = new Merchant *[MAX_NUM_MERCHANT];
	maxNumMerchant = MAX_NUM_MERCHANT;
	numMerchant = 0;
	for (int i = 0; i < MAX_NUM_MERCHANT; i++) {
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				merchant[i] = new Merchant();
				setUnit(randRow, randCol, merchant[i]);
				break;
			}
		}
		numMerchant++;
    }
    
    // create armors
    for (int i = 0; i < MAX_NUM_ARMORS; i++) {
        while (true) { // infinite loop
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(createRandomArmor());
                break;
            }
        }
    }

    // create weapons
    for (int i = 0; i < MAX_NUM_WEAPONS; i++) {
        while (true) { // infinite loop
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(createRandomWeapon());
                break;
            }
        }
    }

    /*
	// create Bow
	for (int i = 0; i < MAX_NUM_BOWS; i++) {
		// put one random Bow
		while (true) { // infinite loop
			int randRow = rand() % rowSize;
			int randCol = rand() % colSize;

			if (board[randRow][randCol]->getProp() == NULL &&
				board[randRow][randCol]->getUnit() == NULL &&
				board[randRow][randCol]->getItem() == NULL) {
				Bow *bow = new Bow();
				board[randRow][randCol]->setItem(bow);
				break;
			}
		}
	}
    */
#endif
}

bool Board::loadLevel(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //--------------------------------------------------------------------------
    // read rowSize and colSize from level file
    //--------------------------------------------------------------------------

    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "buf:" << buf << endl;
    //out << rowSize << endl;
    in >> rowSize;
    in.get(); // skip enter code.

    cout << "rowSize: " << rowSize << endl;
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> colSize;
    in.get(); // skip enter code.
    
    cout << "colSize: " << colSize << endl;

    // create board 
    board = new Tile **[rowSize];
    
    for (int i = 0; i < rowSize; i++) {
        board[i] = new Tile *[colSize];
    }
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j] = new Tile(i, j);
        }
    }
    
    initFx();
    exited = false;

    //--------------------------------------------------------------------------
    // read board from level file
    //--------------------------------------------------------------------------

    //out << "#---------------------------------------- board[][] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "skipped: " << buf << endl;
    
    int countMonster = 0;
    int countBoss = 0;
    int countMerchant = 0;
    int countGhost = 0;
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            char curShape = in.get();
            cout << curShape;
            
            board[i][j] = new Tile(i, j);
            
            Unit *unit = createUnitByShape(curShape);
            if (unit != NULL) {
                setUnit(i, j, unit);
                
                if (unit->isHero()) {
                    hero = (Hero *)unit;
                }
                else if (unit->isBoss()) {
                    countBoss++;
                }
                else if (unit->isMonster()) {
                    countMonster++;
                }
                else if (unit->isMerchant()) {
                    countMerchant++;
                }
                else if (unit->isGhost()) {
                    countGhost++;
                }
            }
            
            Item *item = createItemByShape(curShape);
            if (item != NULL) {
                setItem(i, j, item);
            }
            
            Prop *prop = createPropByShape(curShape);
            if (prop != NULL) {
                setProp(i, j, prop);
            }
        }
        in.get(); // skip enter code at end of the current row
        cout << endl;
    }
    
    //out << "#---------------------------------------- board[][] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "skipped: " << buf << endl;

    // create monsters
    mons = new Monster *[countMonster];
    maxNumMons = countMonster;
    numMons = 0;
    
    boss = new Boss *[countBoss];
    maxNumBoss = countBoss;
    numBoss = 0;
    
    merchant = new Merchant *[countMerchant];
    maxNumMerchant = countMerchant;
    numMerchant = 0;
    
    ghost = new Ghost *[countGhost];
    maxNumGhost = countGhost;
    numGhost = 0;

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            Unit *curUnit = board[i][j]->getUnit();
            if (curUnit != NULL) {
                if (curUnit->isBoss()) {
                    boss[numBoss] = (Boss *)curUnit;
                    numBoss++;
                }
                else if (curUnit->isMonster()) {
                    mons[numMons] = (Monster *)curUnit;
                    numMons++;
                }
                else if (curUnit->isMerchant()) {
                    merchant[numMerchant] = (Merchant *)curUnit;
                    numMerchant++;
                }
                else if (curUnit->isGhost()) {
                    ghost[numGhost] = (Ghost *)curUnit;
                    numGhost++;
                }
            }
        }
    }
    
    return true;
}

void Board::initFx() {
    maxNumShockwaves = MAX_NUM_SHOCKWAVES;
    shockwaves = new Shockwave *[maxNumShockwaves];
    numShockwaves = 0;
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        shockwaves[i] = NULL;
    }
}

Board::~Board() {
    destroyFx();
    destroyBoard();
}

void Board::destroyBoard() {
    // destroy the board
    if (board != NULL) {
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                delete board[i][j];
            }
        }
        
        for (int i = 0; i < rowSize; i++) {
            delete [] board[i];
        }
        
        delete [] board;
        board = NULL;
        
        rowSize = 0;
        colSize = 0;
    }
    
    hero = NULL; // hero has been deleted by ~Tile().
    
    // destroy monsters
    if (mons != NULL) {    
        delete [] mons;
        mons = NULL;
        
        maxNumMons = 0;
        numMons = 0;
    }
    
    // destroy boss
    if (boss != NULL) {    
        delete [] boss;
        boss = NULL;
        
        maxNumBoss = 0;
        numBoss = 0;
    }
    
    // destroy merchants
    if (merchant != NULL) {    
        delete [] merchant;
        merchant = NULL;
        
        maxNumMerchant = 0;
        numMerchant = 0;
    }
	// destroy ghosts
	if (ghost != NULL) {
		delete[] ghost;
		ghost = NULL;

		maxNumGhost = 0;
		numGhost = 0;
	}
}

void Board::destroyFx() {
    if (shockwaves != NULL) {
        delete [] shockwaves;
        shockwaves = NULL;
        
        maxNumShockwaves = 0;
        numShockwaves = 0;
    }
}

void Board::nextShockWave() {
    // process all shockwaves -------------------------------------------------- start
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] != NULL) {
            if (!shockwaves[i]->getWaveActivated()) {
                delete shockwaves[i];
                shockwaves[i] = NULL;
                numShockwaves--;
            }
            else {
                shockwaves[i]->print();
            }
        }
    }
    // process all shockwaves end ---------------------------------------------- end
}

void Board::print() {
	for (int j = 0; j < VIEWPORT_HALF_WIDTH * 2 + 1; j++) {
		cout << "=";
	}
	cout << endl;

	int minimapI = 0;
	for (int i = hero->getRow() - VIEWPORT_HALF_HEIGHT; i <= hero->getRow() + VIEWPORT_HALF_HEIGHT; i++) {
		// print 1 row
		for (int j = hero->getCol() - VIEWPORT_HALF_WIDTH; j <= hero->getCol() + VIEWPORT_HALF_WIDTH; j++) {
			if (validate(i, j)) {
				board[i][j]->print();
			}
			else {
				cout << "#";
			}
		}

		cout << "  ";

		if (minimapI < MINIMAP_ROW_SIZE) {
			// print 1 row of minimap
			for (int minimapJ = 0; minimapJ < MINIMAP_COL_SIZE; minimapJ++) {
				bool foundHero = false;
				Unit *tempHero = NULL;
				bool foundMerchant = false;
				Unit *tempMerchant = NULL;
				bool foundBoss = false;
				Unit *tempBoss = NULL;
				for (int ii = minimapI*MINIMAP_CELL_ROW_SIZE; ii < (minimapI + 1)*MINIMAP_CELL_ROW_SIZE; ii++) {
					for (int jj = minimapJ*MINIMAP_CELL_COL_SIZE; jj < (minimapJ + 1)*MINIMAP_CELL_COL_SIZE; jj++) {
						if (validate(ii, jj) &&
							board[ii][jj]->getUnit() != NULL) {
							if (board[ii][jj]->getUnit()->isHero()) {
								foundHero = true;
								tempHero = board[ii][jj]->getUnit();
							}
							else if (board[ii][jj]->getUnit()->isMerchant()) {
								foundMerchant = true;
								tempMerchant = board[ii][jj]->getUnit();
							}
							else if (board[ii][jj]->getUnit()->isBoss()) {
								foundBoss = true;
								tempBoss = board[ii][jj]->getUnit();
							}
						}
					}
				}

				if (foundHero) {
					tempHero->print();
				}
				else if (foundMerchant) {
					tempMerchant->print();
				}
				else if (foundBoss) {
					tempBoss->print();
				}
				else {
					cout << ".";
				}
			}
			minimapI++;
		}
		cout << endl;
	}

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {


			if (validate(i, j)) {
				board[i][j]->print();
			}


			if (hero->getRow() + 1) {
				cout << "#";
			}

			else if (hero->getRow() - 1) {
				cout << "#";

			}

			else if (hero->getCol() + 1) {
				cout << "#";
			}

			else if (hero->getCol() - 1) {
				cout << "#";
			}
		}
		cout << endl;

	}

}

void Board::clearFx(int row, int col) {
    board[row][col]->clearFx();
}

void Board::setFx(int row, int col, char fx) {
    board[row][col]->setFx(fx);
}

void Board::startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                      int row, int col, int skillNumber) {
    if (numShockwaves >= maxNumShockwaves) {
        cout << "error: can't start new shockwave!";
        return;
    }
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] == NULL) {
            shockwaves[i] = createShockwaveBySkillID(waveUnit, waveItem, waveProp,
                                                     row, col, skillNumber);
            shockwaves[i]->start();
            shockwaves[i]->setSkillNumber(skillNumber);
            numShockwaves++;
            break;
        }
    }
}

void Board::startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
               int row, int col, int range, int frameInterval, char fxShape,
               int skillNumber) {
    if (numShockwaves >= maxNumShockwaves) {
        cout << "error: can't start new shockwave!";
        return;
    }
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] == NULL) {
            shockwaves[i] = new Shockwave(waveUnit, waveItem, waveProp, row, col,
                                          range, frameInterval, fxShape,
                                          skillNumber);
            shockwaves[i]->start();
            shockwaves[i]->setSkillNumber(skillNumber);
            numShockwaves++;
            break;
        }
    }
}

int Board::getRowSize() {
    return rowSize;
}

int Board::getColSize() {
    return colSize;
}

Tile *Board::getTile(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col];
}

bool Board::validate(int row, int col) {
    return row >= 0 && row < rowSize && col >= 0 && col < colSize;
}

Hero *Board::getHero() {
    return hero;
}


Unit *Board::getUnit(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }

    return board[row][col]->getUnit();
}

void Board::setUnit(int row, int col, Unit *unit) {
    if (!validate(row, col)) {
        return;
    }
    
    board[row][col]->setUnit(unit);
    if (unit != NULL) {
        unit->setRow(row);
        unit->setCol(col);
    }
}

Item *Board::getThrowableItem(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getThrowableItem();
}

void Board::setThrowableItem(int row, int col, Item *throwableItem) {
    if (!validate(row, col)) {
        return;
    }
    
    board[row][col]->setThrowableItem(throwableItem);
    if (throwableItem != NULL) {
        throwableItem->setRow(row);
        throwableItem->setCol(col);
    }
}

Item *Board::getItem(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getItem();
}

void Board::setItem(int row, int col, Item *item) {
    if (!validate(row, col)) {
        return;
    }
    
    board[row][col]->setItem(item);
}

Prop *Board::getProp(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getProp();
}

void Board::setProp(int row, int col, Prop *prop) {
    if (!validate(row, col)) {
        return;
    }
    
    board[row][col]->setProp(prop);
    if (prop != NULL) {
        prop->setRow(row);
        prop->setCol(col);
    }
}

bool Board::isExited() {
    return exited;
}

void Board::setExited(bool exited) {
    this->exited = exited;
}

bool Board::getDayAndNight() {
    return dayAndNight;
}

void Board::setDayAndNight(bool dayAndNight) {
    this->dayAndNight = dayAndNight;
}

void Board::toggleDayAndNight() {
    dayAndNight = !dayAndNight;
}

void Board::activateTorch() {
	hasTorch = true;
}

void Board::moveDrivableProps(int dir) {
	//car = new Car();
	//int randDir = rand() % NUM_DIRS;

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getProp() != NULL &&
                board[i][j]->getProp()->isCar()) {
                ((Car *)board[i][j]->getProp())->resetVisited();
            }
        }
    }

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getProp() != NULL &&
                board[i][j]->getProp()->isCar() &&
                !((Car *)board[i][j]->getProp())->isVisited()) {
                ((Car *)board[i][j]->getProp())->drive(dir);
            }
		}
		cout << endl;
	}
}

void Board::moveMons() {
    for (int i = 0; i < numMons; i++) {
        if (mons[i]->isDead() && mons[i]->getRow() != -1) {
            setUnit(mons[i]->getRow(), mons[i]->getCol(), NULL);
            mons[i]->setRow(-1);
            mons[i]->setCol(-1);
#ifndef TURN_OFF_RESPAWN
            // schedule MonRespawnEvent
            sim->eventQueue->enqueue(new MonRespawnEvent(mons[i]));
#endif
        }
        else {
            int randDir = rand() % NUM_DIRS;
            mons[i]->move(randDir);
        }
    }
}
void Board::moveGhost() {
	for (int i = 0; i < numGhost; i++) {
		if (ghost[i]->isDead() && ghost[i]->getRow() != -1) {
			setUnit(ghost[i]->getRow(), ghost[i]->getCol(), NULL);
			ghost[i]->setRow(-1);
			ghost[i]->setCol(-1);

#ifndef TURN_OFF_RESPAWN
			sim->eventQueue->enqueue(new GhostRespawnEvent(ghost[i]));
#endif
		}
		else {
			int randDir = rand() % NUM_DIRS;
			ghost[i]->move(randDir);
		}
	}
}
void Board::moveBoss() {
	for (int i = 0; i < numBoss; i++) {
        //cout << "Board::moveBoss(): entry no=" << i << "--------------------------------------" << endl;
        if (boss[i]->isDead() && boss[i]->getRow() != -1) {
            setUnit(boss[i]->getRow(), boss[i]->getCol(), NULL);
            boss[i]->setRow(-1);
            boss[i]->setCol(-1);

#ifndef TURN_OFF_RESPAWN
			sim->eventQueue->enqueue(new BossRespawnEvent(boss[i]));
#endif 
        }
        else {
            int randDir = rand() % NUM_DIRS;
            boss[i]->move(randDir);
        }
	}
}
void Board::moveMerchant() {
	for (int i = 0; i < numMerchant; i++) {
		int randDir = rand() % NUM_DIRS;
		merchant[i]->move(randDir);
	}
}

void Board::triggerAutoProps() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getProp() != NULL &&
                board[i][j]->getProp()->isHolyStatue()) {
                ((HolyStatue *)board[i][j]->getProp())->start();
            }
        }
    }
}

void Board::moveThrowableItems() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getThrowableItem() != NULL &&
                board[i][j]->getThrowableItem()->isThrowableItem()) {
                board[i][j]->getThrowableItem()->resetVisited();
            }
        }
    }
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getThrowableItem() != NULL &&
                board[i][j]->getThrowableItem()->isThrowableItem() &&
                !board[i][j]->getThrowableItem()->isVisited()) {
                board[i][j]->getThrowableItem()->fly();
            }
        }
        cout << endl;
    }
}

void Board::save(ostream &out) {
    out << "#-------------------- class Board" << endl;
   
    out << "# rowSize" << endl;
    out << rowSize << endl;
    out << "# colSize" << endl;
    out << colSize << endl;
    out << "# dir" << endl;
    out << dir << endl;
    
    out << "#================================================ board[][] started" << endl;
    for (int i = 0; i < rowSize; i++) { 
        for (int j = 0; j < colSize; j++) {
            out << "#======================================== board[" << i << "][" << j << "]" << endl;
            board[i][j]->save(out);
        }
    }
    out << "#================================================ board[][] end" << endl;
    
    out << "#================================================ hero" << endl;
    hero->save(out);
    
    out << "#================================================ mons[]" << endl;
    out << "# maxNumMons" << endl;
    out << maxNumMons << endl;
    out << "# numMons" << endl;
    out << numMons << endl;
    for (int i = 0; i < maxNumMons; i++) {
        out << "#======================================== mons[" << i << "]" << endl;
        mons[i]->save(out);
    }
	out << "#================================================ ghost[]" << endl;
	out << "# maxNumGhost" << endl;
	out << maxNumGhost << endl;
	out << "# numGhost" << endl;
	out << numGhost << endl;
	for (int i = 0; i < maxNumGhost; i++) {
		out << "#======================================== ghost[" << i << "]" << endl;
		ghost[i]->save(out);
	}
    out << "#================================================ boss[]" << endl;
    out << "# maxNumBoss" << endl;
    out << maxNumBoss << endl;
    out << "# numBoss" << endl;
    out << numBoss << endl;
    for (int i = 0; i < maxNumBoss; i++) {
        out << "#======================================== boss[" << i << "]" << endl;
        boss[i]->save(out);
    }

    out << "#================================================ merchant[]" << endl;
    out << "# maxNumMerchant" << endl;
    out << maxNumMerchant << endl;
    out << "# numMerchant" << endl;
    out << numMerchant << endl;
    for (int i = 0; i < maxNumMerchant; i++) {
        out << "#======================================== merchant[" << i << "]" << endl;
        merchant[i]->save(out);
    }
}

void Board::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    destroyBoard();
    destroyFx();
    
    //out << "#-------------------- class Board" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> rowSize;
    in.get(); // skip enter code.
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> colSize;
    in.get(); // skip enter code.
    
    //out << "# dir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << dir << endl;
    in >> dir;
    in.get(); // skip enter code.

    //==========================================================================
    // load board
    //==========================================================================
    board = new Tile **[rowSize];
    
    for (int i = 0; i < rowSize; i++) {
        board[i] = new Tile *[colSize];
    }
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j] = new Tile(i, j);
        }
    }
    
    initFx();
    
    //out << "#================================================ board[][] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            //out << "#======================================== board[" << i << "][" << j << "]" << endl;
            in.getline(buf, MAX_LEN_BUF); // skip comment
            board[i][j]->load(in); // it does not read unit info.
        }
    }
    //out << "#================================================ board[][] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //==========================================================================
    // load hero
    //==========================================================================
    //out << "#================================================ hero" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    hero = new Hero();
    hero->load(in);
    setUnit(hero->getRow(), hero->getCol(), hero);
    
    //==========================================================================
    // load monsters
    //==========================================================================
    
    //out << "#================================================ mons[]" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    //out << "# maxNumMons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumMons << endl;
    in >> maxNumMons;
    in.get(); // skip enter code.

    //out << "# numMons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numMons << endl;
    in >> numMons;
    in.get(); // skip enter code.

    mons = new Monster *[maxNumMons];
    
    for (int i = 0; i < maxNumMons; i++) {
        //out << "#======================================== mons[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment

        mons[i] = new Monster();
        mons[i]->load(in);
        setUnit(mons[i]->getRow(), mons[i]->getCol(), mons[i]);
    }
	//==========================================================================
	// load ghosts
	//==========================================================================

	//out << "#================================================ ghost[]" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment

								  //out << "# maxNumGhost" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
								  //out << maxNumGhost << endl;
	in >> maxNumGhost;
	in.get(); // skip enter code.

			  //out << "# numMons" << endl;
	in.getline(buf, MAX_LEN_BUF); // skip comment
								  //out << numGhost << endl;
	in >> numGhost;
	in.get(); // skip enter code.

	ghost = new Ghost *[maxNumGhost];

	for (int i = 0; i < maxNumGhost; i++) {
		//out << "#======================================== mons[" << i << "]" << endl;
		in.getline(buf, MAX_LEN_BUF); // skip comment

		ghost[i] = new Ghost();
		ghost[i]->load(in);
		setUnit(ghost[i]->getRow(), ghost[i]->getCol(), ghost[i]);
	}

    //==========================================================================
    // load bosses
    //==========================================================================
    
    //out << "#================================================ boss[]" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# maxNumBoss" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumBoss << endl;
    in >> maxNumBoss;
    in.get(); // skip enter code.
    
    //out << "# numBoss" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numBoss << endl;
    in >> numBoss;
    in.get(); // skip enter code.
    
    boss = new Boss *[maxNumBoss];
    
    for (int i = 0; i < maxNumBoss; i++) {
        //out << "#======================================== boss[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        boss[i] = new Boss();
        boss[i]->load(in);
        setUnit(boss[i]->getRow(), boss[i]->getCol(), boss[i]);
    }
    
    //==========================================================================
    // load merchants
    //==========================================================================
    
    //out << "#================================================ merchant[]" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# maxNumMerchant" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumMerchant << endl;
    in >> maxNumMerchant;
    in.get(); // skip enter code.
    
    //out << "# numMerchant" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numMerchant << endl;
    in >> numMerchant;
    in.get(); // skip enter code.
    
    merchant = new Merchant *[maxNumMerchant];
    
    for (int i = 0; i < maxNumMerchant; i++) {
        //out << "#======================================== merchant[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        merchant[i] = new Merchant();
        merchant[i]->load(in);
        setUnit(merchant[i]->getRow(), merchant[i]->getCol(), merchant[i]);
    }
}
