#include "Player.h"

int Player::getId() const {
    return id;
}

int Player::getX() const {
    return x;
}

void Player::setX(int x) {
    this->x = x;
}

int Player::getY() const {
    return y;
}

void Player::setY(int y) {
    this->y = y;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getBombsCount() const {
    return bombsCount;
}

void Player::setBombsCount(int bombsCount) {
    this->bombsCount = bombsCount;
}

int Player::getBombsRadius() const {
    return bombsRadius;
}

int Player::getBombsDelay() const {
    return bombsDelay;
}