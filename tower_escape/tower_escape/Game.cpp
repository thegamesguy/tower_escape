//
//  Game.cpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "Game.hpp"

Game::Game() : window_("Game", sf::Vector2u(640, 380)),
state_manager_(shared_context_)
{
    shared_context_.window_ = &window_;
    shared_context_.event_manager_ = window_.GetEventManager();
    
    state_manager_.SwitchTo(StateType::kIntro);
}

Game::~Game(){}

void Game::HandleInput()
{
    
}

void Game::Update()
{
    window_.Update();
    state_manager_.Update(elapsed_);
}

void Game::LateUpdate()
{
    state_manager_.ProcessRequests();
    RestartClock();
}

void Game::Render()
{
    window_.BeginDraw();
    state_manager_.Draw();
    window_.EndDraw();
}

Window* Game::GetWindow()
{
    return &window_;
}

sf::Time Game::GetElapsed()
{
    return elapsed_;
}

void Game::RestartClock()
{
    elapsed_ = clock_.restart(); // Variable time-step.
    
    // Fixed time-step:
    // elapsed_ += clock_.restart();
    // float frame_time = 1.0f / 60.0f; (Target rate of 60 times a second).
    // if(elapsed_.asseconds() >= frametime) {
    //  execute fixed time-step method
    //  elapsed_ -=sf::seconds(frametime) (Resets cycle)
    // }
}
