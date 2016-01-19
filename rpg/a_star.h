#ifndef A_STAR_H
#define A_STAR_H

#include "dllcontainer.h"
#include "sllcontainer.h"

class Tile;

class AStar {
protected:
    
	void initAStar();
	void deleteAStar();
public:
	AStar();
	AStar(AStar &other);

	virtual ~AStar();
    
    void resetAStar();
    float distance(int startRow, int startCol, int goalRow, int goalCol);
	int neighbourCount(Tile *current);
	bool isNeighbour(Tile *tile1, Tile *tile2);
	void getNeighbours(Tile *current,int neighbour[7]);
    bool checkGoal(Tile *current, Tile *goal);

    DLLContainer<Tile *> *findPath(int startRow, int startCol, int goalRow, int goalCol);
    DLLContainer<Tile *> *reconstructPath(Tile *current);
    
    int countNumTilesWithGivenH(SLLContainer *set, int h);
    void getTilesWithGivenH(SLLContainer *set, int h, Tile **tilesWithGivenH);

//	void print() const;
//
//	void insert(Tile *tile);
//
//	bool isEmpty() const;
//	int size() const; // int getNumItems();
//	int capacity() const;
//
//	Tile *removeTileAt(int indexToRemove);
//	Tile *getTileAt(int indexToReturn);

//	virtual void save(ostream &out) const;
//	virtual void load(istream &in);
};

#endif
