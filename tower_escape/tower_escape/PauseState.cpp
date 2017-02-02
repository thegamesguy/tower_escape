//
//  PauseState.cpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "PauseState.hpp"
#include "StateManager.hpp"

PauseState::PauseState(StateManager& state_manager) : BaseState(state_manager)
{
    
}

PauseState::~PauseState()
{
    
}

void PauseState::OnCreate()
{
    SetTransparent(true);
    
    title_font_.loadFromFile(resourcePath() + "operational_amplifier.ttf");
    title_.setFont(title_font_);
    title_.setCharacterSize(22);
    title_.setFillColor(sf::Color::White);
    title_.setString("PAUSED");
    title_.setStyle(sf::Text::Bold);
    
    sf::Vector2u window_size = state_manager_.GetContext().window_->GetRenderWindow().getSize();
    sf::FloatRect text_rect = title_.getLocalBounds();
    title_.setOrigin(text_rect.left + text_rect.width * 0.5f, text_rect.top + text_rect.height * 0.5f);
    title_.setPosition(window_size.x * 0.5f, window_size.y * 0.3f);
    
    background_.setSize(sf::Vector2f(window_size));
    background_.setPosition(0, 0);
    background_.setFillColor(sf::Color(0, 0, 0, 150));
    
    state_manager_.GetContext().event_manager_->AddCallback(StateType::kPaused, "key_escape", &PauseState::Resume, this);
}

void PauseState::OnDestroy()
{
    state_manager_.GetContext().event_manager_->RemoveCallback(StateType::kPaused, "key_escape");
}

void PauseState::Activate()
{
    
}

void PauseState::Deactivate()
{
    
}

void PauseState::Update(const sf::Time &time)
{
    
}

void PauseState::Draw()
{
    Window* window = state_manager_.GetContext().window_;
    
    window->Draw(background_);
    window->Draw(title_);
}

void PauseState::Resume(EventDetails *details)
{
    state_manager_.SwitchTo(StateType::kGame);
}
