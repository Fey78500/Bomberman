#include "Bomb.h"

Player* Bomb::getOwner() const {
    return owner;
}

int Bomb::getX() const {
    return x;
}

int Bomb::getY() const {
    return y;
}

int Bomb::getDelay() const {
    return delay;
}

int Bomb::getRadius() const {
    return radius;
}

void Bomb::setDelay(int delay) {
    this->delay = delay;
}
