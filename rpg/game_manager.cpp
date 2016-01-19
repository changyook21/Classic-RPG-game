#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#include "main.h"
#include "game.h"
#include "util.h"
#include "game_manager.h"

unsigned gRandSeed = 0;

GameManager::GameManager() {
    
    campaignFilename = "";
    
    title = NULL;
    titleRowSize = 0;
    titleColSize = 0;
    
    ending = NULL;
    endingRowSize = 0;
    endingColSize = 0;
    
    numLevels = 0;
    levelFilenames = 0;
    currentLevelIndex = -1;
    
    currentLevel = NULL;
}

GameManager::~GameManager() {
    if (title != NULL) {
        for (int i = 0; i < titleRowSize; i++) {
            delete [] title[i];
        }
        delete [] title;
        title = NULL;
    }

    if (ending != NULL) {
        for (int i = 0; i < endingRowSize; i++) {
            delete [] ending[i];
        }
        delete [] ending;
        ending = NULL;
    }

    if (levelFilenames != NULL) {
        for (int i = 0; i < numLevels; i++) {
            delete [] levelFilenames[i];
        }
        delete [] levelFilenames;
        levelFilenames = NULL;
        currentLevelIndex = -1;
    }

    if (currentLevel != NULL) {
        delete currentLevel;
        currentLevel = NULL;
    }
}

void GameManager::start() {
    gRandSeed = (unsigned)time(NULL);
    srand(gRandSeed); // init random function.
    //srand(0); // init random function.
    
    while (true) {
        cout << "=======================================================" << endl;
        cout << "===================== Main Menu =======================" << endl;
        cout << "=======================================================" << endl;
        cout << "(L)oad a level / (C)ampaign / (R)andom map / (Q)uit : ";
        while (!_kbhit()) {}
#ifdef VISUAL_STUDIO
        char command = _getch();
#else
        char command = getchar();
#endif 
        cout << endl;
        
        if (command == 'l') {
            string filename = "";    
            cout << "Enter the filename to load ('q' to cancel): ";
            cin >> filename;
            
            if (filename != "q") {
                ifstream fin;
                fin.open(filename.c_str());
                cout << "hello: filename=" << filename << endl;
                if (fin.fail()) {
                    cout << "error: failed to open the file!!" << endl;
                }
                else {
                    Game *game = new Game();
                    game->loadLevel(fin);
                    fin.close();
                    game->play();
                    delete game;
                }
            }
        }
        if (command == 'c') {
            if (loadCampaign()) {
                bool gameOver = false;
                while (!gameOver) {
                    currentLevel->play();
                    // the player cleared the current level.
                    if (currentLevel->getPlayResult()) {
                        if (currentLevelIndex+1 == numLevels) {
                            showEnding();
                            break;
                        }
                        while (true) {
                            cout << "Next Level? (Y/n) : ";
                            char command;
                            cin >> command;
                            cin.get();
                            
                            if (command == 'y') {
                                if (!loadNextLevel()) {
                                    cout << "fatal error: failed to load next level!!!" << endl;
                                    gameOver = true;
                                }
                                break;
                            }
                            else if (command == 'n') {
                                gameOver = true;
                                break;
                            }
                        }
                    }
                    // the player has not been cleared the current level.
                    else {
                        while (true) {
                            cout << "Play again? (Y/n) : ";
                            char command;
                            cin >> command;
                            
                            if (command == 'y') {
                                delete currentLevel;
                                currentLevel = NULL;
                                loadCurrentLevel();
                                break;
                            }
                            else if (command == 'n') {
                                gameOver = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        else if (command == 'r') {
            Game *game = new Game();
            game->initGameRandomly();
            game->play();
            delete game;
        }
        else if (command == 'q') {
            break;
        }
    }
}

bool GameManager::loadCampaign() {
    campaignFilename = "";
    
    cout << "Enter the campaign filename ('q' to cancel): ";
    cin >> campaignFilename;
    cin.get();
    
    if (campaignFilename == "q") {
        return false;
    }
    
    ifstream in;
    in.open(campaignFilename.c_str());
    
    if (in.fail()) { // error
        cout << "error: failed to open the campaign file \"" << campaignFilename << "\"." << endl;
        in.close();
        return false;
    }
    
    // load campaign start
    char buf[MAX_LEN_BUF];
    
    //======================================================================
    // load title screen
    //======================================================================
    
    //#-------------------------------------------------------------------------------
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> titleRowSize;
    in.get(); // skip enter code.

    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> titleColSize;
    in.get(); // skip enter code.
    
    title = new char *[titleRowSize];
    
    for (int i = 0; i < titleRowSize; i++) {
        title[i] = new char [titleColSize+1];
        in.getline(buf, MAX_LEN_BUF); // skip comment
#ifdef VISUAL_STUDIO
		strncpy_s(title[i], titleColSize + 1, buf, titleColSize + 1);
#else
		strncpy(title[i], buf, titleColSize + 1);
#endif 
    }
    
    //======================================================================
    // load level filenames
    //======================================================================
    
    //#-------------------------------------------------------------------------------
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# numLevels" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << buf << endl;
    
    //out << numLevels << endl;
    in >> numLevels;
    in.get(); // skip enter code.
    
    levelFilenames = new char *[numLevels];
    
    for (int i = 0; i < numLevels; i++) {
        //out << "# Level #?" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        levelFilenames[i] = new char [MAX_LEN_FILENAME+1];
        in.getline(buf, MAX_LEN_BUF); // read filename
#ifdef VISUAL_STUDIO
		strncpy_s(levelFilenames[i], MAX_LEN_FILENAME, buf, MAX_LEN_FILENAME);
#else
		strncpy(levelFilenames[i], buf, MAX_LEN_FILENAME);
#endif 
	}
    
    //======================================================================
    // load ending credit
    //======================================================================
    
    //#-------------------------------------------------------------------------------
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> endingRowSize;
    in.get(); // skip enter code.
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> endingColSize;
    in.get(); // skip enter code.
    
    ending = new char *[endingRowSize];
    
    for (int i = 0; i < endingRowSize; i++) {
        ending[i] = new char [endingColSize+1];
        in.getline(buf, MAX_LEN_BUF); // skip comment
#ifdef VISUAL_STUDIO
		strncpy_s(ending[i], endingColSize + 1, buf, endingColSize + 1);
#else
		strncpy(ending[i], buf, endingColSize + 1);
#endif 
    }
    
    in.close();
    
    //======================================================================
    // load first level
    //======================================================================
    showTitle(); // show the campaign title.
    
    currentLevelIndex = 0;
    return loadCurrentLevel();
}

bool GameManager::loadNextLevel() {
    if (currentLevel != NULL) {
        delete currentLevel;
    }
    currentLevelIndex++;
    return loadCurrentLevel();
}

bool GameManager::loadCurrentLevel() {
    currentLevel = new Game();
    ifstream fin;
    fin.open(levelFilenames[currentLevelIndex]);
    if (fin.fail()) {
        cout << "error: failed to open the file!! 1" << endl;
        return false;
    }
    else {
//        Game *game = new Game();
        currentLevel->loadLevel(fin);
        fin.close();
        return true;
    }
}

void GameManager::showTitle() {
    if (title) {
        for (int i = 0; i < titleRowSize; i++) {
            cout << title[i] << endl;
        }
        
        while (!_kbhit()) {}
        getchar();
    }
}

void GameManager::showEnding() {
    if (ending) {
        for (int i = 0; i < endingRowSize; i++) {
            cout << ending[i] << endl;
        }
        
        while (!_kbhit()) {}
        getchar();
    }
}
