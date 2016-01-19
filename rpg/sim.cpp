#include "unit.h"
#include "board.h"
#include "eventqueue.h"
//#include "statistics.h"
#include "sim.h"

Sim::Sim() {
}

void Sim::init() {
    time = 0;
    simulationTime = 1 * 365 * 24 * 3600 * 10; // how long
    
    eventQueue = new EventQueue();
    //    stat = new Statistics();

    board = new Board();
    board->initBoard();
    
    hero = board->getHero();
}

void Sim::init(istream &in) {
    time = 0;
    simulationTime = 1 * 365 * 24 * 3600 * 10; // how long
    
    board = new Board();
    if (!board->loadLevel(in)) {
        delete board;
        cout << "error: Sim::init(istream &) board->loadLevel() returned false" << endl;
        exit(1);
    }    
    hero = board->getHero();
    
    eventQueue = new EventQueue();
//    stat = new Statistics();
}

Sim::~Sim() {
//    deletes stat;
    delete eventQueue;
    delete board;
    // * hero는 여기에서 지우지 않음.
}
