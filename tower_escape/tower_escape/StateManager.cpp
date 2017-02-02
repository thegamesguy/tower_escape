//
//  StateManager.cpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "StateManager.hpp"
#include "IntroState.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

StateManager::StateManager(SharedContext& context) : shared_context_(context)
{
    // Register states
    RegisterState<IntroState>(StateType::kIntro);
    RegisterState<MainMenuState>(StateType::kMainMenu);
    RegisterState<GameState>(StateType::kGame);
    RegisterState<PauseState>(StateType::kPaused);
}

StateManager::~StateManager()
{
    for(auto& itr : states_)
    {
        itr.second->OnDestroy();
        delete itr.second;
    }
}

void StateManager::Draw()
{
    if(states_.empty()){
        return;
    }
    
    if(states_.size() > 1 && states_.back().second->IsTransparent()){
        
        auto itr = states_.end();
        
        while (itr != states_.begin()) {
            if(itr != states_.end()) {
                if(!itr->second->IsTransparent()){
                    break;
                }
            }
            
            --itr;
        }
        
        for (; itr != states_.end(); ++itr) {
            itr->second->Draw();
        }
        
    } else {
        states_.back().second->Draw();
    }
}

void StateManager::Update(const sf::Time &time)
{
    if(states_.empty()){
        return;
    }
    
    if(states_.size() > 1 && states_.back().second->IsTranscendent()){
        
        auto itr = states_.end();
        
        while (itr != states_.begin()) {
            if(itr != states_.end()) {
                if(!itr->second->IsTranscendent()){
                    break;
                }
            }
            
            --itr;
        }
        
        for (; itr != states_.end(); ++itr) {
            itr->second->Update(time);
        }
        
    } else {
        states_.back().second->Update(time);
    }
}

SharedContext& StateManager::GetContext()
{
    return shared_context_;
}

bool StateManager::HasState(const StateType &state_type)
{
    for(auto itr = states_.begin(); itr != states_.end(); ++itr)
    {
        if (itr->first == state_type) {
            auto removed = std::find(states_to_remove_.begin(),
                                     states_to_remove_.end(),
                                     state_type);
            
            if(removed == states_to_remove_.end()){
                return true;
            }
            
            return false;
        }
    }
    
    return false;
}

void StateManager::Remove(const StateType &state_type)
{
    states_to_remove_.emplace_back(state_type);
}

void StateManager::ProcessRequests()
{
    while (states_to_remove_.begin() != states_to_remove_.end()) {
        RemoveState(*states_to_remove_.begin());
        states_to_remove_.erase(states_to_remove_.begin());
    }
}

void StateManager::SwitchTo(const StateType& state_type)
{
    shared_context_.event_manager_->SetCurrentState(state_type);
    
    for (auto itr = states_.begin(); itr != states_.end(); ++itr) {
        if(itr->first == state_type)
        {
            states_.back().second->Deactivate();
            
            StateType temp_type = itr->first;
            
            BaseState* temp_state = itr->second;
            
            states_.erase(itr);
            
            states_.emplace_back(temp_type, temp_state);
            
            temp_state->Activate();
            
            return;
        }
    }
    
    // State to switch to was not found.
    if (!states_.empty()) {
        states_.back().second->Deactivate();
    }
    
    CreateState(state_type);
    
    states_.back().second->Activate();
}

void StateManager::CreateState(const StateType& state_type)
{
    auto new_state = state_factory_.find(state_type);
    
    if (new_state == state_factory_.end()) {
        return;
    }
    
    BaseState* state = new_state->second();
    
    states_.emplace_back(state_type, state);
    
    state->OnCreate();
}

void StateManager::RemoveState(const StateType &state_type)
{
    for (auto itr = states_.begin(); itr != states_.end(); ++itr) {
        if (itr->first == state_type) {
            itr->second->OnDestroy();
            delete itr->second;
            states_.erase(itr);
            return;
        }
    }
}
