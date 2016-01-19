#ifndef SHOCKWAVE_H
#define SHOCKWAVE_H

class Unit;
class Item;
class Prop;
class Board;

class Shockwave {
protected:
    bool waveActivated;
    
    int waveStartRow;
    int waveStartCol;
    int waveMaxRange;
    int waveCurPhase;
    int waveFrameInterval; // to skip frames
    int waveCountFrames;
    int waveFxShape;

    Unit *waveUnit;
    Item *waveItem;
    Prop *waveProp;

    bool drawn;

    int skillNumber;

    // private helper functions
    virtual void removePrevious();
    virtual void drawCurrentPhase();
    virtual void checkCurrentPhase();
    
public:
    
    Shockwave();
    Shockwave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
              int row, int col, int range, int frameInterval, char fxShape,
              int skillNumber);

    virtual ~Shockwave();
    
    void start();
    void stop();
    void print();
    
    int getSkillNumber();
    void setSkillNumber(int skillNumber);
    
    bool getWaveActivated();
};

Shockwave *createShockwaveBySkillID(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                                    int row, int col, int skillNumber);

class AntiCross : public Shockwave {
protected:
    
    // private helper functions
    virtual void removePrevious();
    virtual void drawCurrentPhase();

public:
    AntiCross();
    AntiCross(Unit *waveUnit, Item *waveItem, Prop *waveProp, int row, int col,
              int skillNumber);
    
    virtual ~AntiCross();
};

#endif
