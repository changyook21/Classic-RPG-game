#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <fstream>

using namespace std;

class Hero;
class EventQueue;
class Boss;
class Board;
class Statistics;

// Singleton
class Sim {
public:
    int time;
    int simulationTime; // how long
    
    Board *board;
    Hero *hero;
    
    EventQueue *eventQueue;
//    Statistics *stat;
    
    Sim();
    ~Sim();
    
    void init();
    void init(istream &in);
};

#endif
