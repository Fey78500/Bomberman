#ifndef BOMBERMAN_AI_H
#define BOMBERMAN_AI_H


#include <string>

class Player {
private:
    int id;
    int bombRadius;
    int bombDuration;
    int nbBombs;
    int nbActions;

    void init();
    void initPlayer();
    void initSettings();
    void initTurn(const int& turn);
    void startAction(const int& turn) const;
    void stopAction(const int& turn) const;
    void randomAct();

public:
    Player();
    
    int getId() const;
    void setId(int id);
    
    int getBombRadius() const;
    void setBombRadius(int bombRadius);

    int getBombDuration() const;
    void setBombDuration(int bombDuration);
    
    int getNbBombs() const;
    void setNbBombs(int nbBombs);

    int getNbActions() const;
    void setNbActions(int nbActions);

    void play(const int& turn);
    void goUp() const;
    void goDown() const;
    void goLeft() const;
    void goRight() const;
    void putBomb() const;
    void doNothing() const;
};


#endif
