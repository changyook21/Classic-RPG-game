#include <iostream>

using namespace std;

#include "main.h"
#include "event.h"
#include "eventqueue.h"

EventQueue::EventQueue() {
	head = NULL;  
    numNodes = 0;
    
    //curIter = NULL;
}

EventQueue::~EventQueue() {
    EVNode *current = head;
    
    while (current != NULL) {
        EVNode *nodeToDelete = current;
        
        current = current->next;
        
        delete nodeToDelete->elem;
        delete nodeToDelete;
    }
    
    head = NULL;
    numNodes = 0;
    
    //curIter = NULL;
}

void EventQueue::print() {
	if (head == NULL) { // size() == 0
	}
	else if (head->next == NULL) { // size() == 1
		cout << head->elem << endl;
	}
	else { // size() > 1
		EVNode *current = head;

		while (current != NULL) {
			cout << current->elem << " ";

			current = current->next;
		}
		cout << endl;
	}
}

int EventQueue::size() {
    return numNodes;
}

// ordered by time of Event
bool EventQueue::enqueue(Event *elem) {
    EVNode *newNode = new EVNode(elem);
	if (head == NULL) { // size() == 0
		head = newNode;
		numNodes++;
		return true;
	}
	else if (head->next == NULL) { // size() == 1
		if (elem->time < head->elem->time) { // prepend
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
		EVNode *prev = NULL;
		EVNode *current = head;

		while (current != NULL) {
			if (elem->time < current->elem->time) {
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
Event *EventQueue::dequeue() {
    if (head == NULL) { // size() == 0
        return NULL;
    }
    else { // size() > 1
        Event *elemRemoved = head->elem;
        EVNode *nodeToRemove = head;

        head = head->next;
        numNodes--;
        
        delete nodeToRemove;
        return elemRemoved;
    }
}

Event *EventQueue::peek() {
    if (head == NULL) { // size() == 0
        return NULL;
    }

    return head->elem;
}

bool EventQueue::hasMore() {
    return curIter != NULL;
}

// pre-condition: hasMore() == true
Event *EventQueue::next() {
    Event *elemToReturn = curIter->elem;
    curIter = curIter->next;
    return elemToReturn;
}

void EventQueue::resetIterator() {
    curIter = head;
}
