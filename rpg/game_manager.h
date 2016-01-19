#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>

using namespace std;

class Game;

class GameManager {
protected:
    string campaignFilename;
    
    //Screen *title;
    char **title;
    int titleRowSize;
    int titleColSize;
    
    //Screen *ending;
    char **ending;
    int endingRowSize;
    int endingColSize;
    
    int numLevels;
    char **levelFilenames;
    int currentLevelIndex;
    
    Game *currentLevel;
    
public:
    GameManager();
    virtual ~GameManager();
    
    void start();
    
    bool loadCampaign();
    bool loadNextLevel();
    bool loadCurrentLevel();
    
    void showTitle();
    void showEnding();
};

#endif
