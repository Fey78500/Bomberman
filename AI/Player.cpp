#include "Player.h"
#include <iostream>


Player::Player() {
    this->init();
}

int Player::getId() const {
    return id;
}

void Player::setId(int id) {
    this->id = id;
}

int Player::getBombDuration() const {
    return bombDuration;
}

void Player::setBombDuration(int bombDuration) {
    this->bombDuration = bombDuration;
}

int Player::getBombRadius() const {
    return bombRadius;
}

void Player::setBombRadius(int bombRadius) {
    this->bombRadius = bombRadius;
}

int Player::getNbBombs() const {
    return nbBombs;
}

void Player::setNbBombs(int nbBombs) {
    this->nbBombs = nbBombs;
}

int Player::getNbActions() const {
    return nbActions;
}

void Player::setNbActions(int nbActions) {
    this->nbActions = nbActions;
}

void Player::init() {
    this->initPlayer();
    this->initSettings();
}

void Player::startAction(const int& turn) const {
    std::cout << "START action " << turn << std::endl;
}

void Player::stopAction(const int& turn) const {
    std::cout << "STOP action " << turn << std::endl;
}

void Player::goUp() const {
    std::cout << "U" << std::endl;
}

void Player::goDown() const {
    std::cout << "D" << std::endl;
}

void Player::goLeft() const {
    std::cout << "L" << std::endl;
}

void Player::goRight() const {
    std::cout << "R" << std::endl;
}

void Player::putBomb() const {
    std::cout << "B" << std::endl;
}

void Player::doNothing() const {
    std::cout << "NOACTION" << std::endl;
}

void expectMessage(const std::string& message) {
    std::string input;
    std::getline(std::cin, input);
    if (input != message) {
        std::cout << "Expected input was '" + message + "', '" + input + "' received";
        throw std::exception();
    }
}

int idInput() {
    std::string input;
    std::getline(std::cin, input);
    int inputId = std::stoi(input);

    if (std::cin.fail()) {
        throw std::exception();
    }

    return inputId;
}


void Player::initPlayer() {
    expectMessage("START player");
    this->setId(idInput());
    expectMessage("STOP player");
}

void Player::initSettings() {
    expectMessage("START settings");
    std::string inputSetting;
    do {
        std::getline(std::cin, inputSetting);
    } while(inputSetting != "STOP settings");
}

void Player::initTurn(const int& turn) {
    expectMessage("START turn " + std::to_string(turn));
    expectMessage("STOP turn " + std::to_string(turn));
}

void Player::play(const int& turn) {
    this->initTurn(turn);
    this->startAction(turn);
    this->setNbActions(1);
    for (int i = 0; i < this->getNbActions(); i++) {
         this->randomAct();
    }

    this->stopAction(turn);
    
}

void Player::randomAct() {
char letters[] = "ULDRBN";
char x = letters[rand() % 6];
    switch (x) {
        case 'U':
            this->goUp();
            break;
        case 'D':
            this->goDown();
            break;
        case 'L':
            this->goLeft();
            break;
        case 'R':
            this->goRight();
            break;
        case 'B':
            this->putBomb();
            break;
        case 'N':
            this->doNothing();
            break;
        default:
            this->doNothing();
            break;
    }
}
