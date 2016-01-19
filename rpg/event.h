#ifndef EVENT_H
#define EVENT_H

class Monster;
class Ghost;
class Boss;
class Item;


class Event {
public:
    int time;

    Event();
    Event(int time);
    virtual ~Event();
    
    virtual void print();
    
    virtual void trigger() = 0; // pure virtual function.
};

class MonRespawnEvent : public Event {
protected:
    Monster *mon;
    
public:
    MonRespawnEvent();
    MonRespawnEvent(Monster *mon);
    MonRespawnEvent(int time, Monster *mon);

    virtual ~MonRespawnEvent();
        
    virtual void trigger();
};

class BossRespawnEvent : public Event {
protected:
	Boss *boss;

public:
	BossRespawnEvent();
	BossRespawnEvent(Boss *boss);
	BossRespawnEvent(int time, Boss *boss);

	virtual ~BossRespawnEvent();

	virtual void trigger();
};

class GhostRespawnEvent : public Event {
protected:
	Ghost *ghost;

public:
	
	GhostRespawnEvent();
	GhostRespawnEvent(Ghost *ghost);
	GhostRespawnEvent(int time, Ghost *ghost);

	virtual ~GhostRespawnEvent();

	virtual void trigger();
};

class DayNight : public Event {
protected:
    int interval;
public:
	DayNight();
    DayNight(int time, int interval);
	virtual ~DayNight();

	virtual void trigger();
};

class TimeBomb : public Event {
protected:
	Item *bomb;
	int row;
	int col;
	int range;

public:
	TimeBomb();
	TimeBomb(Item *bomb);
	TimeBomb(int time, Item *bomb);

	virtual ~TimeBomb();

	virtual void trigger();
};


#endif
