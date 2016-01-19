#include <iostream>

using namespace std;

#include "tile.h"
#include "sllcontainer.h"

SLLContainer::SLLContainer() {
	head = NULL;  
    numNodes = 0;
    
    //curIter = NULL;
}

SLLContainer::~SLLContainer() {
    SLLNode *current = head;
    
    while (current != NULL) {
        SLLNode *nodeToDelete = current;
        
        current = current->next;
        delete nodeToDelete;
    }
    
    head = NULL;
    numNodes = 0;
    
    //curIter = NULL;
}

void SLLContainer::print() {
	if (head == NULL) { // size() == 0
	}
	else if (head->next == NULL) { // size() == 1
		cout << head->elem << endl;
	}
	else { // size() > 1
		SLLNode *current = head;

		while (current != NULL) {
			cout << current->elem << " ";

			current = current->next;
		}
		cout << endl;
	}
}

int SLLContainer::size() {
    return numNodes;
}

bool SLLContainer::isEmpty() {
    return numNodes == 0;
}

// find() checks whether the list has the given tile(Tile *) or not.
bool SLLContainer::find(Tile *elem) {
	if (head == NULL) { // size() == 0
		return false;
	}
	else if (head->next == NULL) { // size() == 1
		if (elem == head->elem) {
			return true;
		}
		else {
			return false;
		}
	}
	else { // size() > 1
		SLLNode *current = head;

		while (current != NULL) {
			if (elem == current->elem) {
				return true;
			}

			current = current->next;
		}
		//  current가 NULL되어서 빠져나왔다는 것은, 결국 못 찾았다는 말이므로, NULL을 return.
		return false;
	}
}

// ordered by f score
bool SLLContainer::insert(Tile *elem) {
    if (find(elem)) { // duplicate!
        return false;
    }
    
    SLLNode *newNode = new SLLNode(elem);
	if (head == NULL) { // size() == 0
		head = newNode;
		numNodes++;
		return true;
	}
	else if (head->next == NULL) { // size() == 1
        // when the f score of the given tile is greater than or equal to the head,
        // then it will be appended.
		if (elem->f < head->elem->f) { // prepend
			newNode->next = head;
			head = newNode;
			numNodes++;
			return true;
		}
		else { // append
			head->next = newNode;
			numNodes++;
			return true;
		}
	}
	else { // size() > 1
		SLLNode *prev = NULL;
		SLLNode *current = head;

		while (current != NULL) {
			if (elem->f < current->elem->f) {
				break;
			}

			prev = current;
			current = current->next;
		}

		// 끼워넣을 장소
		if (prev == NULL) { // prepend
			newNode->next = head;
			head = newNode;
			numNodes++;
			return true;
		}
		else if (current == NULL) { // append
			prev->next = newNode;
			numNodes++;
			return true;
		}
		else { // insert the new node between prev and current
			prev->next = newNode;
			newNode->next = current;
			numNodes++;
			return true;
		}
	}
}

// pre-condition: size() > 0
Tile *SLLContainer::removeGetMinFScoreTile() {
    if (head == NULL) { // size() == 0
        return NULL;
    }
    else { // size() > 1
        Tile *elemRemoved = head->elem;
        SLLNode *nodeToRemove = head;

        head = head->next;
        numNodes--;
        
        delete nodeToRemove;
        return elemRemoved;
    }
}

// pre-condition: size() > 0
Tile *SLLContainer::getMinHScoreTile() {
    if (head == NULL) { // size() == 0
        return NULL;
    }
    else { // size() > 1
        int minH = head->elem->h;
        Tile *curMinTile = head->elem;
        
        SLLNode *current = head->next;
        
        while (current != NULL) {
            if (minH > current->elem->h) {
                minH = current->elem->h;
                curMinTile = current->elem;
            }
            
            current = current->next;
        }
        
        return curMinTile;
    }
}

bool SLLContainer::hasMore() {
    return curIter != NULL;
}

// pre-condition: hasMore() == true
Tile *SLLContainer::next() {
    Tile *elemToReturn = curIter->elem;
    curIter = curIter->next;
    return elemToReturn;
}

void SLLContainer::resetIterator() {
    curIter = head;
}
