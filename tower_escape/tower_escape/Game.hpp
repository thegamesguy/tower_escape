//
//  Game.hpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

//#include <stdio.h>
#include "Window.hpp"
#include "StateManager.hpp"

class Game {
    
public:
    Game();
    ~Game();
    
    void HandleInput();
    void Update();
    void LateUpdate();
    void Render();
    
    Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();
    
private:
    Window window_;
    sf::Clock clock_;
    sf::Time elapsed_;
    SharedContext shared_context_;
    StateManager state_manager_;
};

#endif /* Game_hpp */
