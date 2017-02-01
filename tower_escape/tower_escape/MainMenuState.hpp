//
//  MainMenuState.hpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include <stdio.h>
#include "BaseState.hpp"

class MainMenuState : public BaseState {
public:
    MainMenuState(StateManager& state_manager);
    ~MainMenuState();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& time);
    void Draw();
    
    void MenuSelectionUp(EventDetails* event_details);
    void MenuSelectionDown(EventDetails* event_details);
    
private:
    sf::Font font_;
    sf::Text menu_title_text_;
    sf::Vector2f button_size_;
    sf::Vector2f button_position_;
    unsigned int button_padding_px_;
    
    sf::RectangleShape rects[3];
    sf::Text labels[3];

};

#endif /* MainMenuState_hpp */
