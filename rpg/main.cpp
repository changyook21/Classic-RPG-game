#include "game_manager.h"

int main() {
    GameManager *gm = new GameManager();
    gm->start();
    delete gm;
    return 0;
}
