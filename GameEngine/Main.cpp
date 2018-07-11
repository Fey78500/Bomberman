//
// Created by Fey-u on 25/06/2018.
//
#include <iostream>
#include <getopt.h>
#include <fstream>
#include "Level.h"

//Verification si une entrée est un chiffre
bool is_digit(std::string str) {
    for (char i : str) {
        if (!isdigit(i)) {
            return false;
        }
    }

    return true;
}

//Initiation du game engine via le fichier de config (game-engine.cfg)
void initConfigFromFile(const std::string& filePath, int& mapWidth, int& mapHeight, int& bombsCount, int& bombsDelay, int& bombsRadius, bool& randomWalls, bool& gridRing, int& deadline, int& breakableWallsRate, int& wallsDensity, int& baseHealth) {
    std::ifstream file(filePath);
    std::string key;
    int value;

    if (!file) {
        return;
    }

    while (file >> key >> value) {
        if (key == "GRID_WIDTH") mapWidth = value;
        else if (key == "GRID_HEIGHT") mapHeight = value;
        else if (key == "GRID_WALLS_DENSITY") wallsDensity = value;
        else if (key == "GRID_BREAKABLE_WALLS_RATE") breakableWallsRate = value;
        else if (key == "GRID_RING") gridRing = static_cast<bool>(value);
        else if (key == "BOMBS_COUNT") bombsCount = value;
        else if (key == "BOMBS_DELAY") bombsDelay = value;
        else if (key == "BOMBS_RADIUS") bombsRadius = value;
        else if (key == "GAME_WALLS_RANDOM") randomWalls = static_cast<bool>(value);
        else if (key == "GAME_DEADLINE") deadline = value;
        else if (key == "PLAYERS_BASE_HEALTH") baseHealth = value;
    }
}

//Initiation de la configuration
void initConfig(int argc, char* argv[], int& mapWidth, int& mapHeight, int& bombsCount, int& bombsDelay, int& bombsRadius, bool& randomWalls, bool& gridRing, int& deadline, int& breakableWallsRate, int& wallsDensity, int& baseHealth, std::string& configFile) {
    int ch;
    while ((ch = getopt(argc, argv, "hW:H:b:d:r:i:B:s:p:wRGf:")) != -1) {
        switch (ch) {
            case 'h':
                std::cout << "Usage: bomberman-engine.exe [options]\nOptions:\n"
                             "\t-W <NUMBER>\tMap width (default: 20).\n"
                             "\t-H <NUMBER>\tMap height (default: 20).\n"
                             "\t-b <NUMBER>\tMaximum simultaneous bombs a player can use (default: 2).\n"
                             "\t-d <NUMBER>\tDelay after which the bombs explode (default: 5).\n"
                             "\t-r <NUMBER>\tBombs explosion radius. (default: 5)\n"
                             "\t-p <NUMBER>\tGrid walls density. (default: 20)\n"
                             "\t-s <NUMBER>\tPlayers base health. (default: 1)\n"
                             "\t-B <NUMBER>\tBreakable walls rate. (default: 30)\n"
                             "\t-D\t\tDeadline before players are automatically killed (default: 0)\n"
                             "\t-w\t\tRandom walls placement.\n"
                             "\t-R\t\tMap is a ring\n"
                             "\t-f <PATH>\tConfiguration file. If set, these configs will override CLI parameters.\n";
                exit(0);
            case 'W':
                mapWidth = is_digit(optarg) ? std::stoi(optarg): mapWidth;
                break;
            case 'H':
                mapHeight = is_digit(optarg) ? std::stoi(optarg): mapHeight;
                break;
            case 'b':
                bombsCount = is_digit(optarg) ? std::stoi(optarg): bombsCount;
                break;
            case 'd':
                bombsDelay = is_digit(optarg) ? std::stoi(optarg) : bombsDelay;
                break;
            case 'r':
                bombsRadius = is_digit(optarg) ? std::stoi(optarg) : bombsRadius;
                break;
            case 'B':
                breakableWallsRate = is_digit(optarg) ? std::stoi(optarg) : breakableWallsRate;
                break;
            case 'D':
                deadline = is_digit(optarg) ? std::stoi(optarg) : deadline;
            case 's':
                baseHealth = is_digit(optarg) ? std::stoi(optarg) : baseHealth;
                break;
            case 'p':
                wallsDensity = is_digit(optarg) ? std::stoi(optarg) : wallsDensity;
            case 'w':
                randomWalls = true;
                break;
            case 'R':
                gridRing = true;
                break;
            case 'f':
                initConfigFromFile(optarg, mapWidth, mapHeight, bombsCount, bombsDelay, bombsRadius, randomWalls, gridRing, deadline, breakableWallsRate, wallsDensity, baseHealth);
                return;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    int turn = 0;
    int mapWidth = 20;
    int mapHeight = 20;
    int bombsCount = 2;
    int bombsDelay = 5;
    int bombsRadius = 5;
    bool randomWalls = false;
    bool gridRing = false;
    int deadline = 0;
    int baseHealth = 1;
    int wallsDensity = 20;
    int breakableWallsRate = 30;
    std::string configFile;

    initConfig(argc, argv, mapWidth, mapHeight, bombsCount, bombsDelay, bombsRadius, randomWalls, gridRing, deadline, breakableWallsRate, wallsDensity, baseHealth, configFile);
    auto * gameEngine = new Level(mapWidth, mapHeight, bombsCount, bombsDelay, bombsRadius, randomWalls, gridRing, deadline, breakableWallsRate, wallsDensity, baseHealth);

    while (true) {
        turn++;
        gameEngine->update();

        for (auto &player : gameEngine->getPlayers()) {
            gameEngine->playerTurn(turn, player);
        }

        if (gameEngine->getPlayersLeft() <= 1 || (gameEngine->getPlayersLeft() > 1 && gameEngine->getDeadline() > 0 && gameEngine->getDeadline() == turn)) {
            break;
        }
    }

    return 0;
}