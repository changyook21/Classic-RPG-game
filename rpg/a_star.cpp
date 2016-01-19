#include <iostream>

using namespace std;

#include "tile.h"
#include "board.h"
#include "a_star.h"

//extern Board *sim->board;
#include "sim.h"
extern Sim *sim;

AStar::AStar() {
}

void AStar::initAStar() {
}

AStar::AStar(AStar &other) {
}

AStar::~AStar() {
	deleteAStar();
}

void AStar::deleteAStar() {
}

void AStar::resetAStar() {
    for (int i = 0; i < sim->board->getRowSize(); i++) {
        for (int j = 0; j < sim->board->getColSize(); j++) {
            sim->board->getTile(i, j)->clearAStar();
        }
    }
}

float AStar::distance(int startRow, int startCol, int goalRow, int goalCol) {
    float x = (float)(fabs(startRow - goalRow));
    float y = (float)(fabs(startCol - goalCol));
    
    return x + y;
}

int AStar::neighbourCount(Tile *current) {
	int neighbours = 0;

	for (int i = 0; i < sim->board->getRowSize(); i++) {
		for (int j = 0; j < sim->board->getColSize(); j++) {
			if (sim->board->getTile(i, j) == current) {
				//check the available neighbours
                if (sim->board->validate(i - 1, j) &&
                    sim->board->board[i - 1][j]->getProp() == NULL &&
                    sim->board->board[i - 1][j]->getUnit() == NULL) {
                    
                    neighbours++;
                }
                if (sim->board->validate(i, j + 1) &&
                    sim->board->board[i][j + 1]->getProp() == NULL &&
                    sim->board->board[i][j + 1]->getUnit() == NULL) {
                    
                    neighbours++;
                }
				if (sim->board->validate(i + 1, j) &&
					sim->board->board[i + 1][j]->getProp() == NULL &&
					sim->board->board[i + 1][j]->getUnit() == NULL) {

					neighbours++;
				}
				if (sim->board->validate(i, j - 1) &&
					sim->board->board[i][j - 1]->getProp() == NULL &&
					sim->board->board[i][j - 1]->getUnit() == NULL) {

					neighbours++;
				}
				return neighbours;
			}
		}
	}
    
    return 0;
}

bool AStar::isNeighbour(Tile *tile1, Tile *tile2) {
	for (int i = 0; i < sim->board->getRowSize(); i++) {
		for (int j = 0; j < sim->board->getColSize(); j++) {
			if (sim->board->getTile(i, j) == tile1) {
				if (sim->board->getTile(i + 1, j) == tile2 ||
					sim->board->getTile(i - 1, j) == tile2 ||
					sim->board->getTile(i, j + 1) == tile2 ||
					sim->board->getTile(i, j - 1) == tile2) {

					return true;
				}
				else {
					return false;
				}
			}
		}
	}

	return false;

}

void AStar::getNeighbours(Tile *current, int neighbours[8]) {
    int inc = 0;
    
    int curRow = current->row;
    int curCol = current->col;
    
    if (sim->board->validate(curRow - 1, curCol) &&
        sim->board->board[curRow - 1][curCol]->getProp() == NULL &&
        sim->board->board[curRow - 1][curCol]->getUnit() == NULL) {
        neighbours[inc] = curRow - 1;
        inc++;
        neighbours[inc] = curCol;
        inc++;
    }
    if (sim->board->validate(curRow, curCol + 1) &&
        sim->board->board[curRow][curCol + 1]->getProp() == NULL &&
        sim->board->board[curRow][curCol + 1]->getUnit() == NULL) {
        neighbours[inc] = curRow;
        inc++;
        neighbours[inc] = curCol + 1;
        inc++;
    }
    if (sim->board->validate(curRow + 1, curCol) &&
        sim->board->board[curRow + 1][curCol]->getProp() == NULL &&
        sim->board->board[curRow + 1][curCol]->getUnit() == NULL) {
        neighbours[inc] = curRow + 1;
        inc++;
        neighbours[inc] = curCol;
        inc++;
    }
    if (sim->board->validate(curRow, curCol - 1) &&
        sim->board->board[curRow][curCol - 1]->getProp() == NULL &&
        sim->board->board[curRow][curCol - 1]->getUnit() == NULL) {
        neighbours[inc] = curRow;
        inc++;
        neighbours[inc] = curCol - 1;
        inc++;
    }
}

bool AStar::checkGoal(Tile *current, Tile *goal) {
    int curRow = current->row;
    int curCol = current->col;
    
    int goalRow = goal->row;
    int goalCol = goal->col;
    
    if (curRow-1 == goalRow && curCol == goalCol) {
        return true;
    }
    if (curRow == goalRow && curCol+1 == goalCol) {
        return true;
    }
    if (curRow+1 == goalRow && curCol == goalCol) {
        return true;
    }
    if (curRow == goalRow && curCol-1 == goalCol) {
        return true;
    }
    return false;
}

//==============================================================================
// function A*(start,goal)
//==============================================================================
DLLContainer<Tile *> *AStar::findPath(int startRow, int startCol, int goalRow, int goalCol) {
    char astarStep = 'A';
    
    resetAStar();
    Tile *start = sim->board->getTile(startRow, startCol);
    Tile *goal = sim->board->getTile(goalRow, goalCol);
    
    //ClosedSet := {}    	  // The set of nodes already evaluated.
    SLLContainer *closedSet = new SLLContainer();
    
    //OpenSet := {start}    // The set of tentative nodes to be evaluated, initially containing the start node
    SLLContainer *openSet = new SLLContainer();
    openSet->insert(start);
    
    //Came_From := the empty map    // The map of navigated nodes.
    //***** resetAStar() clears map
    
    //g_score := map with default value of Infinity
    //***** resetAStar() init all the map with INF
    
    //g_score[start] := 0    // Cost from start along best known path.
    start->g = 0;
    
    //// Estimated total cost from start to goal through y.
    
    //f_score := map with default value of Infinity
    //***** resetAStar() init all the map with INF
    
    //f_score[start] := g_score[start] + heuristic_cost_estimate(start, goal)
    start->h = (int)distance(startRow, startCol, goalRow, goalCol);
    start->f = start->g + start->h;

    //while OpenSet is not empty
    while (!openSet->isEmpty()) {
        //current := the node in OpenSet having the lowest f_score[] value
        Tile *current = openSet->removeGetMinFScoreTile();

        //ClosedSet.Add(current)
        closedSet->insert(current);
        
        current->astarStep = astarStep;
        //sim->board->print();
        if (astarStep >= 'A' && astarStep <= 'Z') {
            if (astarStep == 'Z') {
                astarStep = 'a';
            }
            else {
                astarStep++;
            }
        }
        else if (astarStep >= 'a' && astarStep <= 'z') {
            if (astarStep == 'z') {
                astarStep = 'A';
            }
            else {
                astarStep++;
            }
        }
        
        //if current = goal
        if (current == goal) {
            delete openSet;
            delete closedSet;

            //return reconstruct_path(Came_From, goal)
            return reconstructPath(goal);
        }
        // if the goal is adjacent to the current(N, E, S, or W)
        else if (checkGoal(current, goal)) {
            delete openSet;
            delete closedSet;
            
            goal->cameFrom = current;
            //return reconstruct_path(Came_From, goal)
            return reconstructPath(goal);
        }
            
        //OpenSet.Remove(current)
		//*****openSet->removeGetMinFScoreTile();

        //for each neighbor of current
		int count = neighbourCount(current);
		int neighboursTile[8];
		getNeighbours(current, neighboursTile);
#ifdef DEBUG_MSG_ASTAR
        cout << "-------------------------------------------------" << endl;
        cout << "current->row=" << current->row << " / current->col=" << current->col << endl;
        cout << "current->f=" << current->f << " / current->g=" << current->g << " / current->h=" << current->h << endl;
        cout << "count=" << count << endl;
#endif
		for (int i = 0; i < count*2; i+=2) {
#ifdef DEBUG_MSG_ASTAR
            cout << "i=" << i << endl;
            cout << "neighboursTile[i]=" << neighboursTile[i] << " / neighboursTile[i + 1]=" << neighboursTile[i + 1] << endl;
#endif
			Tile *neighbour = sim->board->getTile(neighboursTile[i], neighboursTile[i + 1]);
			//if neighbor in ClosedSet	
			if (closedSet->find(neighbour)) {
				//continue		// Ignore the neighbor which is already evaluated.
#ifdef DEBUG_MSG_ASTAR
                cout << "skipped: it is in closedSet!" << endl;
#endif
				continue;
			}
			//tentative_g_score := g_score[current] + dist_between(current,neighbor) // length of this path.
			//since neighbour will always be horizontal or vertical, +10 for each tile
			int tentative_g_score = current->g + 1; 
			//if neighbor not in OpenSet	// Discover a new node
			if (!openSet->find(neighbour)) {
                //// This path is the best until now. Record it!
                //Came_From[neighbor] := current
                neighbour->cameFrom = current;
                //g_score[neighbor] := tentative_g_score
                neighbour->g = tentative_g_score;
                //f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
                neighbour->h = (int)distance(neighbour->row, neighbour->col, goalRow, goalCol);
                neighbour->f = neighbour->g + neighbour->h;

				openSet->insert(neighbour);
			}
			//else if tentative_g_score >= g_score[neighbor] 
			else if (tentative_g_score >= neighbour->g){
#ifdef DEBUG_MSG_ASTAR
                cout << "skipped: it is in openSet! new g score is not less than previous one!" << endl;
#endif
				//continue		// This is not a better path.
				continue;
			}
            else {
                //// This path is the best until now. Record it!
                //Came_From[neighbor] := current
                neighbour->cameFrom = current;
                //g_score[neighbor] := tentative_g_score
                neighbour->g = tentative_g_score;
                //f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
                neighbour->h = (int)distance(neighbour->row, neighbour->col, goalRow, goalCol);
                neighbour->f = neighbour->g + neighbour->h;
            }
		}
    }

#ifdef DEBUG_MSG_ASTAR
    cout << "AStar::findPath(): no path!" << endl;
#endif
 
    // The goal should be nearest point.
    Tile *tileWithMinH = closedSet->getMinHScoreTile();
#ifdef DEBUG_MSG_ASTAR
    cout << "AStar::findPath(): tileWithMinF=" << tileWithMinH << endl;
#endif
    
    int minH = tileWithMinH->h;
#ifdef DEBUG_MSG_ASTAR
    cout << "AStar::findPath(): minH=" << minH << endl;
#endif
    
    int numTilesWithGivenH = countNumTilesWithGivenH(closedSet, minH);
#ifdef DEBUG_MSG_ASTAR
    cout << "AStar::findPath(): numTilesWithGivenH=" << numTilesWithGivenH << endl;
#endif

    Tile **tilesWithGivenH = new Tile *[numTilesWithGivenH];
    getTilesWithGivenH(closedSet, minH, tilesWithGivenH);
    
    int minLenPath = INF;
    int indexMinLenPath = -1;
    Tile *tileMinLenPathIndex = NULL;
    
    for (int i = 0; i < numTilesWithGivenH; i++) {
        Tile *curFakeGoal = tilesWithGivenH[i];
#ifdef DEBUG_MSG_ASTAR
        cout << "tilesWithGivenH[" << i << "]=(" << curFakeGoal->row << ", " << curFakeGoal->col << ")" << endl;
#endif
        DLLContainer<Tile *> *curPath = reconstructPath(curFakeGoal);
#ifdef DEBUG_MSG_ASTAR
        cout << "    curPath->size()=" << curPath->size() << endl;
#endif
        if (minLenPath > curPath->size()) {
            minLenPath = curPath->size();
            indexMinLenPath = i;
            tileMinLenPathIndex = curFakeGoal;
#ifdef DEBUG_MSG_ASTAR
            cout << "    min updated: i=" << i << endl;
#endif
        }
    }
    
    delete openSet;
    delete closedSet;
    
    return reconstructPath(tileMinLenPathIndex);
    //return failure
    //return NULL;
}

int AStar::countNumTilesWithGivenH(SLLContainer *set, int h) {
    int count = 0;
    
    set->resetIterator();
    
    while (set->hasMore()) {
        Tile *curTile = set->next();
        if (curTile->h == h) {
            count++;
        }
    }
    return count;
}

void AStar::getTilesWithGivenH(SLLContainer *set, int h, Tile **tilesWithGivenH) {
    int index = 0;
    
    set->resetIterator();
    
    while (set->hasMore()) {
        Tile *curTile = set->next();
        if (curTile->h == h) {
            tilesWithGivenH[index] = curTile;
            index++;
        }
    }
}

//==============================================================================
//function reconstruct_path(Came_From,current)
//==============================================================================
DLLContainer<Tile *> *AStar::reconstructPath(Tile *current) {
	//SLLContainer *total_path = new SLLContainer();
    // create a stack to hold the path.
    DLLContainer<Tile *> *total_path = new DLLContainer<Tile *>();
    
	//total_path := [current]
	total_path->pushBack(current);
    
	//while current in Came_From.Keys:
	while (current->cameFrom != NULL) {
		//current := Came_From[current]
		current = current->cameFrom;
		//total_path.append(current)
		total_path->pushBack(current);
	}
	//return total_path
    return total_path;
}
