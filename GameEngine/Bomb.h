#ifndef ENGINE_BOMB_H
#define ENGINE_BOMB_H


#include "Player.h"

class Bomb {
private:
    int x;
    int y;
    int delay;
    int radius;
    Player* owner;

public:
    Bomb(Player* owner, int x, int y, int delay, int radius) : owner(owner), x(x), y(y), delay(delay), radius(radius) {}
    Player* getOwner() const;
    int getX() const;
    int getY() const;
    int getDelay() const;
    int getRadius() const;

    void setDelay(int delay);

};


#endif
