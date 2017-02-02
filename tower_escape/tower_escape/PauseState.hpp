//
//  PauseState.hpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef PauseState_hpp
#define PauseState_hpp

#include <stdio.h>
#include "BaseState.hpp"
#include "ResourcePath.hpp"

class PauseState : public BaseState {
public:
    PauseState(StateManager& state_manager);
    ~PauseState();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& time);
    void Draw();
    
    void Resume(EventDetails* details);
    
private:
    sf::Font title_font_;
    sf::Text title_;
    sf::RectangleShape background_;
};

#endif /* PauseState_hpp */
