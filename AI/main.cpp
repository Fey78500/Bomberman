#include <iostream>
#include "Player.h"

int main()
{
    int turn = 1;
    auto *player = new Player();

    while (true)
    {
        player->play(turn);
        turn++;
    }

    return 0;
}
