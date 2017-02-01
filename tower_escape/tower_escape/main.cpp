// Created:         31/01/2017
// Author:          Robert Wells
// Description:     Entry point into game.


#include "Game.hpp"
#include "ResourcePath.hpp"

int main(int, char const**)
{

    
    Game game;
    
    while (!game.GetWindow()->IsDone()) {
        
        game.HandleInput();
        game.Update();
        game.Render();
        game.LateUpdate();
        
    }
    
    
    return EXIT_SUCCESS;
}
