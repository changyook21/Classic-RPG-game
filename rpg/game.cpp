#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#include "main.h"
#include "unit.h"
#include "monster.h"
#include "item.h"
#include "prop.h"
#include "tile.h"
#include "board.h"
#include "util.h"
#include "game.h"
#include "event.h"
#include "eventqueue.h"

//Board *sim->board = NULL;
//int sim->time = 0;
#include "sim.h"
Sim *sim = NULL;

extern unsigned gRandSeed;

Game::Game() {
}

Game::~Game() {
//    delete sim->board;
//    sim->board = NULL;
//    hero = NULL;
    delete sim;
    sim = NULL;
}

void Game::initGameRandomly() {
    sim = new Sim();
    sim->init();
    
    playResult = false;
}

void Game::loadLevel(istream &in) {
    sim = new Sim();
    sim->init(in);
    
    playResult = false;
}

void Game::play() {
//    EventQueue *evList = new EventQueue();
//
//    evList->enqueue(new Event(20));
//    evList->enqueue(new Event(30));
//    evList->enqueue(new Event(10));
//    evList->enqueue(new Event(50));
//    evList->enqueue(new Event(40));
//    
//    while (evList->size() > 0) {
//        Event *curEvent = evList->dequeue();
//        curEvent->print();
//        cout << endl;
//        delete curEvent;
//    }
//    
//    delete evList;
//    exit(1);
    
    sim->board->print();
    
    sim->time = 0;
    
    playResult = false;
    
    while (true) {
        cout << "gRandSeed: " << gRandSeed << endl;
        
        while (sim->eventQueue->size() > 0 && sim->eventQueue->peek()->time <= sim->time) {
            Event *curEvent = sim->eventQueue->dequeue();
            curEvent->trigger();
		
            //delete curEvent; // DO NOT DELETE
        }
        
        //int dir = rand() % 4;
        int dir = -1;
        bool bounceKeyPressed = false;
        
        if (_kbhit()) {
#ifdef VISUAL_STUDIO
            char command = _getch();
#else
            char command = getchar();
#endif 
            if (command == KEY_N) {
                dir = DIR_N;
            }
            else if (command == KEY_E) {
                dir = DIR_E;
            }
            else if (command == KEY_S) {
                dir = DIR_S;
            }
            else if (command == KEY_W) {
                dir = DIR_W;
            }
            
            if (command == KEY_N_BOUNCE) {
                dir = DIR_N;
                bounceKeyPressed = true;
            }
            else if (command == KEY_E_BOUNCE) {
                dir = DIR_E;
                bounceKeyPressed = true;
            }
            else if (command == KEY_S_BOUNCE) {
                dir = DIR_S;
                bounceKeyPressed = true;
            }
            else if (command == KEY_W_BOUNCE) {
                dir = DIR_W;
                bounceKeyPressed = true;
            }
            
            //------------------------------------------------------------------
            // handle "use keys"
            //------------------------------------------------------------------
            if (command >= '1' && command <= '5') {
                sim->hero->useItem(command-'1');
            }
            
            //------------------------------------------------------------------
            // handle "get off"
            //------------------------------------------------------------------
            if (command == 'q') {
                sim->hero->kickout();
            }
            
            //------------------------------------------------------------------
            // handle "show wave" command
            //------------------------------------------------------------------
            if (command == 'e') {
                sim->board->startWave(NULL, NULL, NULL,
                                  sim->hero->getRow(), sim->hero->getCol(),
                                  SHOCKWAVE_ANTICROSS_ID);
            }
		
			
            //------------------------------------------------------------------
            // handle "unequip" command
            //------------------------------------------------------------------
            if (command == 'u') {
                int bodyPartNo = -1;
                cout << "Enter the body part number (1-8): ";
                cin >> bodyPartNo;
                sim->hero->unequip(bodyPartNo);
            }
            
            
            
            //------------------------------------------------------------------
            // handle "commandMoveItemsSlotsToBackpack" command
            //------------------------------------------------------------------
            // move an item from hero's slots to the backpack.
            if (command == '.') {
                int indexItemOfSlots = -1;
                cout << "Enter the index of the slots item : ";
                cin >> indexItemOfSlots;
                sim->hero->moveItemFromSlotsToBackpack(indexItemOfSlots-1);
            }
            
            //------------------------------------------------------------------
            // handle "commandMoveItemsBackpackToSlots" command
            //------------------------------------------------------------------
            if (command == ',') {
                int indexItemOfBackpack = -1;
                cout << "Enter the index of the backpack item : ";
                cin >> indexItemOfBackpack;
                int indexItemOfSlots = -1;
                cout << "Enter the index of the slots item : ";
                cin >> indexItemOfSlots;
                sim->hero->moveItemFromBackpackToSlots(indexItemOfBackpack-1, indexItemOfSlots-1);
            }
            
            //------------------------------------------------------------------
            // handle "save" command
            //------------------------------------------------------------------
            if (command == 'o') {
                string filename = "";    
                cout << "Enter the filename to save (q to cancel): ";
                cin >> filename;
                
                if (filename != "q") {
                    ofstream fout;
                    fout.open(filename.c_str());
                    
                    if (fout.fail()) {
                        cout << "error: failed to open the file!!" << endl;
                    }
                    else {
                        sim->board->save(fout);
                    }
                }
            }
            
            //------------------------------------------------------------------
            // handle "load" command
            //------------------------------------------------------------------
            if (command == 'l') {
                string filename = "";    
                cout << "Enter the filename to load (q to cancel): ";
                cin >> filename;
                
                if (filename != "q") {
                    ifstream fin;
                    fin.open(filename.c_str());
                    
                    if (fin.fail()) {
                        cout << "error: failed to open the file!!" << endl;
                    }
                    else {
                        sim->board->load(fin);
                        sim->hero = sim->board->getHero();
                    }
                }
            }
            
            //------------------------------------------------------------------
            // handle "shoot" command
            //------------------------------------------------------------------
            if (command == 'r') {
                sim->hero->shoot();
            }
        }
        
        sim->board->nextShockWave();
        
        if (dir != -1) {
            sim->hero->move(dir, bounceKeyPressed);
        }
		if (sim->time % SPEED_CAR == 0) {
			sim->board->moveDrivableProps(dir);
		}
        if (sim->time % SPEED_AUTO_PROPS == 0) {
            sim->board->triggerAutoProps();
        }
        // throwbale item must move before boss or monster
        if (sim->time % SPEED_ARROW == 0) {
            sim->board->moveThrowableItems();
        }
        
        if (sim->time % SPEED_BOSS == 0) {
            sim->board->moveBoss();
        }
        if (sim->time % SPEED_MONSTER == 0) {
            sim->board->moveMons();
        }
        //if (sim->time % SPEED_MERCHANT == 0) {
        //    sim->board->moveMerchant();
        //}
		if (sim->time % SPEED_GHOST == 0) {
			sim->board->moveGhost();
		}
        sim->board->print();
        cout << "sim->time: " << sim->time << endl;
        sim->hero->printStat();
        
        if (sim->hero->isDead()) {
            cout << "You died!!! Game Over!!" << endl;
            break;
        }

        if (sim->board->isExited()) {
            cout << "Congratulation!!" << endl;
            playResult = true;
            break;
        }

        if (sim->hero->getUnitEngaged() != NULL &&
            sim->hero->getUnitEngaged()->isDead()) {
            sim->hero->setUnitEngaged(NULL);
        }

#ifdef VISUAL_STUDIO
        Sleep(BASE_INTERVAL); // 1,000 = 1 sec
        system("cls");
#else
        usleep(BASE_INTERVAL*1000); // 1,000,000 = 1 sec
#endif
        
        sim->time++;
        
    }
    cout << "Bye!!" << endl;

    //getchar();
}

bool Game::getPlayResult() {
    return playResult;
}
