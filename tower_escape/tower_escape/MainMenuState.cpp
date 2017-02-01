//
//  MainMenuState.cpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "MainMenuState.hpp"
#include "StateManager.hpp"

MainMenuState::MainMenuState(StateManager& state_manager) : BaseState(state_manager)
{
    
}

MainMenuState::~MainMenuState(){}

void MainMenuState::OnCreate()
{
    font_.loadFromFile(resourcePath() + "operational_amplifier.ttf");
    menu_title_text_.setFont(font_);
    menu_title_text_.setString("MAIN MENU");
    menu_title_text_.setCharacterSize(18);
    
    sf::FloatRect text_rect = menu_title_text_.getLocalBounds();
    menu_title_text_.setOrigin(text_rect.left + text_rect.width * 0.5f, text_rect.top + text_rect.height * 0.5f);
    
    menu_title_text_.setPosition(400, 100);
    
    button_size_ = sf::Vector2f(300.0f, 32.0f);
    button_position_ = sf::Vector2f(400.0f, 200.0f);
    button_padding_px_ = 4;
    
    std::string str[3];
    str[0] = "PLAY";
    str[1] = "CREDITS";
    str[2] = "EXIT";
    
    for (int i = 0; i < 3; i++) {
        
        sf::Vector2f button_position_(button_position_.x, button_position_.y + (i * (button_size_.y + button_padding_px_)));
        rects[i].setSize(button_size_);
        rects[i].setFillColor(sf::Color::Red);
        rects[i].setOrigin(button_size_.x / 2.0f, button_size_.y / 2.0f);
        rects[i].setPosition(button_position_);
        labels[i].setFont(font_);
        labels[i].setString(sf::String(str[i]));
        labels[i].setCharacterSize(12);
        sf::FloatRect rect = labels[i].getLocalBounds();
        labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
        labels[i].setPosition(button_position_);
        
    }
    
    EventManager* evt_mngr = state_manager_.GetContext().event_manager_;
    
    evt_mngr->AddCallback(StateType::kMainMenu, "key_up", &MainMenuState::MenuSelectionUp, this);
    evt_mngr->AddCallback(StateType::kMainMenu, "key_down", &MainMenuState::MenuSelectionDown, this);
}

void MainMenuState::OnDestroy()
{
    EventManager* evt_mngr = state_manager_.GetContext().event_manager_;
    
    evt_mngr->RemoveCallback(StateType::kMainMenu, "key_up");
    evt_mngr->RemoveCallback(StateType::kMainMenu, "key_down");
}

void MainMenuState::Activate()
{
    if(state_manager_.HasState(StateType::kGame) && labels[0].getString() == "PLAY") {
        labels[0].setString("RESUME");
        
        sf::FloatRect rect = labels[0].getLocalBounds();
        labels[0].setOrigin(rect.left + rect.width / 2.0f,rect.top + rect.height / 2.0f);
    }
}

void MainMenuState::Deactivate()
{
    
}

void MainMenuState::Update(const sf::Time &time)
{
    
}

void MainMenuState::Draw()
{
    Window* window = state_manager_.GetContext().window_;
    
    window->Draw(menu_title_text_);
    
    for (int i = 0; i < 3; i++) {
        window->Draw(rects[0]);
        window->Draw(labels[i]);
    }
}

void MainMenuState::MenuSelectionUp(EventDetails *event_details)
{
    
}

void MainMenuState::MenuSelectionDown(EventDetails *event_details)
{
    
}
