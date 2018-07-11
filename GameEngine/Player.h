#ifndef ENGINE_PLAYER_H
#define ENGINE_PLAYER_H


#include <vector>

class Player {
private:
    int id;
    int x;
    int y;
    int health;
    int bombsCount;
    int bombsRadius;
    int bombsDelay;

public:
    explicit Player(int id, int health, int bombsCount, int bombsRadius, int bombsDelay, int actionsPerTurn) : id(id), x(0), y(0), health(health), bombsCount(bombsCount), bombsDelay(bombsDelay), bombsRadius(bombsRadius) {}
    int getId() const;
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getBombsCount() const;
    int getBombsRadius() const;
    int getBombsDelay() const;
    void setX(int x);
    void setY(int y);
    void setHealth(int health);
    void setBombsCount(int bombs);
};


#endif
