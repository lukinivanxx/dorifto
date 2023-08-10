#include <iostream>

#include "GameEngine.h"

int main()
{
    GameEngine gameEngine;

    //Game Loop
    while (gameEngine.running()) {
        gameEngine.update();

        gameEngine.render();

    }
}