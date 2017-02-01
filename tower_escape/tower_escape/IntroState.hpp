//
//  IntroState.hpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef IntroState_hpp
#define IntroState_hpp

#include <stdio.h>
#include "BaseState.hpp"
#include "ResourcePath.hpp"

class IntroState : public BaseState {
public:
    IntroState(StateManager& state_manager);
    ~IntroState();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& time);
    void Draw();

    void Continue(EventDetails* event_details);
    
private:
    sf::Texture intro_texture_background_;
    sf::Sprite intro_sprite_background_;
    sf::Texture intro_texture_foreground_;
    sf::Sprite intro_sprite_foreground_;
    sf::Font intro_font_;
    sf::Text intro_text_;
    float time_passed_;
};

#endif /* IntroState_hpp */
