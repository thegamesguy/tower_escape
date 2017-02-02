//
//  GameState.hpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include <stdio.h>
#include "BaseState.hpp"

class GameState : public BaseState {
public:
    GameState(StateManager& state_manager);
    ~GameState();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& time);
    void Draw();
    
    void Pause(EventDetails* details);

private:
    sf::Texture background_texture_;
    sf::Sprite background_sprite_;
};

#endif /* GameState_hpp */
