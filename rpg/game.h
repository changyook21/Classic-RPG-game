#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>

using namespace std;

class Hero;

class Game {
protected:
    bool playResult;
    
public:
    Game();
    virtual ~Game();
    
    void initGameRandomly();
    void loadLevel(istream &in);
    void play();
    
    bool getPlayResult();
};

#endif
