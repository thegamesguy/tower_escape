//
//  GameState.cpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "GameState.hpp"
#include "StateManager.hpp"

GameState::GameState(StateManager& state_manager) : BaseState(state_manager)
{
    
}

GameState::~GameState()
{
    
}

void GameState::OnCreate()
{
    background_texture_.loadFromFile(resourcePath() + "environment.png");
    background_sprite_.setTexture(background_texture_);
    
    state_manager_.GetContext().event_manager_->AddCallback(StateType::kGame, "key_escape", &GameState::Pause, this);
}

void GameState::OnDestroy()
{
    state_manager_.GetContext().event_manager_->RemoveCallback(StateType::kGame, "key_escape");
}

void GameState::Activate()
{
    
}

void GameState::Deactivate()
{
    
}

void GameState::Update(const sf::Time &time)
{
    
}

void GameState::Draw()
{
    state_manager_.GetContext().window_->Draw(background_sprite_);
}

void GameState::Pause(EventDetails *details)
{
    state_manager_.SwitchTo(StateType::kPaused);
}

