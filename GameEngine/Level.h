//
// Created by Fey-u on 25/06/2018.
//
#ifndef ENGINE_GAMEENGINE_H
#define ENGINE_GAMEENGINE_H


#include <string>
#include <vector>
#include "Player.h"
#include "Bomb.h"

class Level {
private:
    int gridWidth;
    int gridHeight;
    int bombsCount;
    int bombsDelay;
    int bombsRadius;
    int actionsPerTurn = 1;
    int playersLeft;
    bool randomWalls;
    bool gridRing;
    int deadline;
    int breakableWallsRate;
    int wallsDensity;
    int baseHealth;
    int spawnArray;
    std::vector<std::string> grid;
    std::vector<Player*> players;
    std::vector<Bomb*> bombs;

    void init();
    void initPlayers();
    void sendSettings();
    void generateGrid();
    void receivePlayers();
    void spawnPlayers();
    void sendGridInformation() const;
    void getPlayerActions(const int& turn, Player* player);
    void applyPlayerAction(Player *player, std::string action);
    void clearGrid();
    void displayBombs();
    void displayPlayers();
    void updateBombs();
    void triggerBomb(Bomb* bomb);
    void triggerBombAtPosition(int x, int y);
    void hitPlayerAtPosition(int x, int y);
    void sendWinner();
    Player* getWinner() const;
    void movePlayer(Player* player, int y, int x);


public:
    Level(int gridWidth, int gridHeight, int bombsCount, int bombsDelay, int bombsRadius, bool randomWalls, bool gridRing, int deadline, int breakableWallsRate, int wallsDensity, int baseHealth);
    int getPlayersLeft() const;
    int getDeadline() const;
    std::vector<Player*> getPlayers() const;
    void playerTurn(int turn, Player* player);
    void update();
};


#endif
