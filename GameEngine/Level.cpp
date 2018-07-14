//
// Created by Fey-u on 25/06/2018.
//
#include "Level.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>
#include <tuple>
#include <random>

//Initialisation de toute les constante
static const char GRID_EMPTY = '_';
static const char GRID_WALL = '#';
static const char GRID_BREAKABLE_WALL = '%';
static const char GRID_BOMB = 'o';
static const char GRID_HORIZONTAL_EXPLOSION = '-';
static const char GRID_VERTICAL_EXPLOSION = '|';
static const std::string ACTION_UP = "U";
static const std::string ACTION_DOWN = "D";
static const std::string ACTION_LEFT = "L";
static const std::string ACTION_RIGHT = "R";
static const std::string ACTION_BOMB = "B";
static const std::string ACTION_NO_ACTION = "NOACTION";

//Constructeur de level
Level::Level(int gridWidth, int gridHeight, int bombsCount, int bombsDelay, int bombsRadius, bool randomWalls, bool gridRing, int deadline, int breakableWallsRate, int wallsDensity, int baseHealth) : gridWidth(gridWidth), gridHeight(gridHeight), bombsCount(bombsCount), bombsDelay(bombsDelay), bombsRadius(bombsRadius), randomWalls(randomWalls), gridRing(gridRing), deadline(deadline), breakableWallsRate(breakableWallsRate), wallsDensity(wallsDensity), baseHealth(baseHealth) {
    this->init();
}

void Level::init() {
    this->initPlayers();
    this->sendSettings();
    this->generateGrid();
    this->spawnPlayers();
}

std::vector<Player*> Level::getPlayers() const {
    return this->players;
}

void Level::generateGrid() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    std::vector<std::string> grid;

    for (int i = 0; i < this->gridHeight; i++) {
        std::string line;

        for (int j = 0; j < this->gridWidth; j++) {
            char ch = GRID_EMPTY;

            if (j == 0 || j == this->gridWidth - 1 || i == 0 || i == this->gridHeight - 1) {
                if (this->gridRing) {
                    int random = dist(engine);
                    if (random < this->wallsDensity) {
                        ch = random < this->breakableWallsRate ? GRID_BREAKABLE_WALL : GRID_WALL;
                    }
                } else {
                    ch = GRID_WALL;
                }
            } else {
                int random = dist(engine);
                if (random < this->wallsDensity) {
                    ch = random < this->breakableWallsRate ? GRID_BREAKABLE_WALL : GRID_WALL;
                }
            }

            line += ch;
        }

        grid.push_back(line);
    }

    this->grid = grid;
}

void Level::spawnPlayers() {
    for (auto &player: players) {
        while (true) {
            std::random_device rd;
            std::default_random_engine engine(rd());
            std::uniform_int_distribution<int> uniform_distX(0, this->gridWidth - 1);
            std::uniform_int_distribution<int> uniform_distY(0, this->gridHeight - 1);
            int x = uniform_distX(engine);
            int y = uniform_distY(engine);
            if (this->grid[y][x] == GRID_EMPTY) {
                player->setX(x);
                player->setY(y);
                break;
            }
        }
    }

}

void expectMessage(const std::string& message) {
    std::string input;
    std::getline(std::cin, input);

    if (input != message) {
        std::cout << "Expected input was '" + message + "', '" + input + "' received";
        throw std::exception();
    }
}

void Level::receivePlayers() {
    std::string input;
    std::getline(std::cin, input);
    int playersCount = std::stoi(input);

    if (std::cin.fail()) {
        throw std::exception();
    }

    this->playersLeft = playersCount;

    for (int id = 1; id < playersCount + 1; id++) {
        auto * player = new Player(id, baseHealth, bombsCount, bombsRadius, bombsDelay, actionsPerTurn);
        this->players.push_back(player);
    }
}

void Level::sendSettings() {
    std::cout << "START settings" << std::endl;
    std::cout << "NB_BOMBS " << this->bombsCount << std::endl;
    std::cout << "BOMB_DURATION " << this->bombsDelay << std::endl;
    std::cout << "BOMB_RADIUS " << this->bombsRadius << std::endl;
    std::cout << "STOP settings" << std::endl;
}

void Level::initPlayers() {
    expectMessage("START players");
    this->receivePlayers();
    expectMessage("STOP players");
}

void Level::sendGridInformation() const {
    std::cout << this->gridWidth << " " << this->gridHeight << std::endl;

    for (int line = 0; line < this->gridHeight; line++) {
        std::cout << this->grid[line] << std::endl;
    }
}

void Level::applyPlayerAction(Player *player, std::string action) {
    int x = player->getX();
    int y = player->getY();

    if (player->getHealth() == 0) {
        return;
    } else if (action == ACTION_NO_ACTION) {
        return;
    } else if (action == ACTION_UP) {
        y--;
    } else if (action == ACTION_DOWN) {
        y++;
    } else if (action == ACTION_LEFT) {
        x--;
    } else if (action == ACTION_RIGHT) {
        x++;
    } else if (action == ACTION_BOMB && player->getBombsCount() > 0) {
        this->bombs.push_back(new Bomb(player, x, y, player->getBombsDelay(), player->getBombsRadius()));
        player->setBombsCount(player->getBombsCount() - 1);
    }

    this->movePlayer(player, y, x);
}

void Level::movePlayer(Player* player, int y, int x) {
    if (this->gridRing) {
        x = x < 0 ? this->gridWidth - 1 : x > this->gridWidth - 1 ? 0 : x;
        y = y < 0 ? this->gridHeight - 1 : y > this->gridHeight - 1 ? 0 : y;
    }

    // TODO : refacto hot fix
    if (this->grid[y][x] != GRID_WALL && this->grid[y][x] != GRID_BREAKABLE_WALL && this->grid[y][x] != '1' && this->grid[y][x] != '2' && this->grid[y][x] != '3' && this->grid[y][x] != '4' && this->grid[y][x] != '5' && this->grid[y][x] != '6' && this->grid[y][x] != '7' && this->grid[y][x] != '8' && this->grid[y][x] != '9') {
        player->setY(y);
        player->setX(x);
    }
}

void Level::getPlayerActions(const int& turn, Player* player) {
    expectMessage("START actions " + std::to_string(turn) + " " + std::to_string(player->getId()));

    std::string action;
    do {
        std::getline(std::cin, action);
        this->applyPlayerAction(player, action);
    } while(action != "STOP actions " + std::to_string(turn) + " " + std::to_string(player->getId()));
}

int Level::getDeadline() const {
    return deadline;
}

Player* Level::getWinner() const {
    Player *winner = nullptr;

    for (auto &player: this->players) {
        if (player->getHealth() > 0) {
            winner = player;
        }
    }

    return winner;
}

void Level::sendWinner() {
    if (this->playersLeft == 0) {
        std::cout << "WINNER 0" << std::endl;
    } else {
        Player* winner = this->getWinner();
        std::cout << "WINNER " << std::to_string(winner->getId()) << std::endl;
    }
}

void Level::playerTurn(int turn, Player* player) {
    std::cout << "START turn " << turn << " " << player->getId() << std::endl;

    if (this->playersLeft <= 1) {
        this->sendWinner();
    } else if (this->playersLeft > 1 && this->deadline > 0 && this->deadline == turn) {
        std::cout << "WINNER 0" << std::endl;
    } else {
        this->sendGridInformation();
    }

    std::cout << "STOP turn " << turn << " " << player->getId() << std::endl;
    this->getPlayerActions(turn, player);
}

void Level::clearGrid() {
    for (int i = 0; i < this->gridHeight; i++) {
        for (int j = 0; j < this->gridWidth; j++) {
            if (this->grid[i][j] != GRID_WALL && this->grid[i][j] != GRID_BREAKABLE_WALL) {
                this->grid[i][j] = GRID_EMPTY;
            }
        }
    }
}

void Level::displayBombs() {
    for (auto &bomb : this->bombs) {
        this->grid[bomb->getY()][bomb->getX()] = GRID_BOMB;
    }
}


void Level::displayPlayers() {
    for (auto &player : this->players) {
        if (player->getHealth() > 0) {
            this->grid[player->getY()][player->getX()] = std::to_string(player->getId())[0];
        }
    }
}

void Level::triggerBombAtPosition(int y, int x) {
    for (auto &bomb : this->bombs) {
        if (bomb->getX() == x && bomb->getY() == y) {
            this->triggerBomb(bomb);
        }
    }
}

int Level::getPlayersLeft() const {
    return this->playersLeft;
}

void Level::hitPlayerAtPosition(int y, int x) {
    for (auto &player : this->players) {
        if (player->getX() == x && player->getY() == y && player->getHealth() > 0) {
            player->setHealth(std::max(player->getHealth() - 1, 0));

            if (player->getHealth() == 0) {
                this->playersLeft--;
                std::cerr << "bomb kills player " <<  player->getId() << " at (x: " << x << ", y: " << y << ")" << std::endl;
            }
        }
    }
}

void Level::updateBombs() {
    for (auto &bomb : this->bombs) {
        if (bomb->getDelay() > 0) {
            bomb->setDelay(bomb->getDelay() - 1);
        } else if (bomb->getDelay() == 0) {
            this->triggerBomb(bomb);
        }
    }
}

void Level::triggerBomb(Bomb* bomb) {
    bomb->getOwner()->setBombsCount(bomb->getOwner()->getBombsCount() + 1);
    auto position = std::find(this->bombs.begin(), this->bombs.end(), bomb);
    if (position != this->bombs.end()) {
        this->bombs.erase(position);
    }

    int x = bomb->getX();
    int y = bomb->getY();

    std::vector<std::tuple<int, int>> directions;
    directions.emplace_back(std::make_tuple(1, 0));
    directions.emplace_back(std::make_tuple(-1, 0));
    directions.emplace_back(std::make_tuple(0, 1));
    directions.emplace_back(std::make_tuple(0, -1));

    for (auto &direction : directions) {
        for (int i = 0; i < bomb->getRadius() + 1; i++ ) {
            int cx = x + i * std::get<0>(direction);
            int cy = y + i * std::get<1>(direction);

            if (cy < 0 || cy > this->gridHeight - 1 || cx < 0 || cx > this->gridWidth - 1) {
                break;
            }

            if (this->grid[cy][cx] == GRID_WALL) {
                break;
            }

            if (this->grid[cy][cx] == GRID_BREAKABLE_WALL) {
                this->grid[cy][cx] = x != cx ? GRID_HORIZONTAL_EXPLOSION : y != cy ? GRID_VERTICAL_EXPLOSION : this->grid[cy][cx];
                break;
            }

            this->grid[cy][cx] = x != cx ? GRID_HORIZONTAL_EXPLOSION : y != cy ? GRID_VERTICAL_EXPLOSION : this->grid[cy][cx];
            this->triggerBombAtPosition(cy, cx);
            this->hitPlayerAtPosition(cy, cx);
        }
    }
}

void Level::update() {
    this->clearGrid();
    this->displayBombs();
    this->displayPlayers();
    this->updateBombs();
}
