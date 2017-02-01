//
//  EventManager.cpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "EventManager.hpp"

EventManager::EventManager() :has_focus_(true)
{
    LoadBindings();
}

EventManager::~EventManager()
{
    for(auto &itr : bindings_)
    {
        delete itr.second;
        itr.second = nullptr;
    }
}

bool EventManager::AddBinding(Binding* binding)
{
    if (bindings_.find(binding->name_) != bindings_.end()) {
        return false;
    }
    
    return bindings_.emplace(binding->name_, binding).second;
}

bool EventManager::RemoveBinding(std::string binding_name)
{
    auto itr = bindings_.find(binding_name);
    
    if(itr != bindings_.end()){
        return false;
    }
    
    delete itr->second;
    bindings_.erase(itr);
    
    return true;
}

void EventManager::SetFocus(const bool& focus)
{
    has_focus_ = focus;
}

bool EventManager::RemoveCallback(StateType state, const std::string& name)
{
    auto itr = callbacks_.find(state);
    if(itr == callbacks_.end()){
        return false;
    }
    
    auto itr2 = itr->second.find(name);
    if(itr2 == itr->second.end()) {
        return false;
    }
    
    itr->second.erase(name);
    
    return true;
}

sf::Vector2i EventManager::GetMousePosition(sf::RenderWindow* window)
{
    return window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
}

void EventManager::HandleEvent(sf::Event &event)
{
    // Handling SFML events.
    for (auto &b_itr : bindings_){
        Binding* bind = b_itr.second;
        for (auto &e_itr : bind->events_){
            EventType sfmlEvent = (EventType)event.type;
            
            if (e_itr.first != sfmlEvent){
                continue;
            }
            
            if (sfmlEvent == EventType::kKeyDown || sfmlEvent == EventType::kKeyUp) {
                if (e_itr.second.key_code_ == event.key.code){
                    // Matching event/keystroke.
                    // Increase count.
                    if (bind->details_.key_code_ != -1){
                        bind->details_.key_code_ = e_itr.second.key_code_;
                    }
                    ++(bind->event_count_);
                    break;
                }
            } else if (sfmlEvent == EventType::kMButtonDown || sfmlEvent == EventType::kMButtonUp) {
                if (e_itr.second.key_code_ == event.mouseButton.button){
                    // Matching event/keystroke.
                    // Increase count.
                    bind->details_.mouse_.x = event.mouseButton.x; bind->details_.mouse_.y = event.mouseButton.y;
                    if (bind->details_.key_code_ != -1){
                        bind->details_.key_code_ = e_itr.second.key_code_;
                    }
                    ++(bind->event_count_);
                    break;
                }
            } else {
                // No need for additional checking.
                if (sfmlEvent == EventType::kMouseWheel){
                    bind->details_.mouse_delta_ = event.mouseWheel.delta;
                } else if (sfmlEvent == EventType::kWindowResized){
                    bind->details_.size_.x = event.size.width;
                    bind->details_.size_.y = event.size.height;
                } else if (sfmlEvent == EventType::kTextEntered){
                    bind->details_.text_entered_ = event.text.unicode;
                }
                
                ++(bind->event_count_);
            }
        }
    }
}

void EventManager::Update()
{
    if (!has_focus_){
        return;
    }
    
    for (auto &b_itr : bindings_){
        Binding* bind = b_itr.second;
        
        for (auto &e_itr : bind->events_){
            switch (e_itr.first){
                case EventType::kKeyboard:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.key_code_))) {
                        if (bind->details_.key_code_ != -1){
                            bind->details_.key_code_ = e_itr.second.key_code_;
                        }
                        ++(bind->event_count_);
                    }
                    break;
                case EventType::kMouse:
                    if (sf::Mouse::isButtonPressed( sf::Mouse::Button(e_itr.second.key_code_))) {
                        if (bind->details_.key_code_ != -1){
                            bind->details_.key_code_ = e_itr.second.key_code_;
                        }
                        ++(bind->event_count_);
                    }
                    break;
                case EventType::kJoystick:
                    // Up for expansion.
                    break;
                    
                // Ignored.
                case EventType::kKeyDown:
                case EventType::kKeyUp:
                case EventType::kMButtonDown:
                case EventType::kMButtonUp:
                case EventType::kMouseWheel:
                case EventType::kWindowResized:
                case EventType::kGainedFocus:
                case EventType::kLostFocus:
                case EventType::kMouseEntered:
                case EventType::kMouseLeft:
                case EventType::kClosed:
                case EventType::kTextEntered:
                    break;
            }
        }
        
        if (bind->events_.size() == bind->event_count_){
            auto state_callbacks = callbacks_.find(current_state_);
            auto other_callbacks = callbacks_.find(StateType(0)); // Global callbacks.
            
            if(state_callbacks != callbacks_.end()) {
                auto call_itr = state_callbacks->second.find(bind->name_);
                
                if(call_itr != state_callbacks->second.end()) {
                    call_itr->second(&bind->details_);
                }
            }
            
            if(other_callbacks != callbacks_.end()) {
                auto call_itr = other_callbacks->second.find(bind->name_);
                
                if(call_itr != other_callbacks->second.end()) {
                    call_itr->second(&bind->details_);
                }
            }
            
        }
        
        bind->event_count_ = 0;
        bind->details_.Clear();
    }
}

void EventManager::SetCurrentState(StateType state)
{
    current_state_ = state;
}

void EventManager::LoadBindings()
{
    std::string delimiter = ":";
    
    std::ifstream bindings;
    
    bindings.open(resourcePath() + "keys.cfg");
    
    if (!bindings.is_open()){
        std::cout << "! Failed loading keys.cfg." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(bindings, line)){
        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;
        Binding* bind = new Binding(callbackName);
        
        while (!keystream.eof()){
            std::string keyval;
            keystream >> keyval;
            int start = 0;
            int end = keyval.find(delimiter);
            
            if (end == std::string::npos){
                delete bind;
                bind = nullptr;
                break;
            }
            
            EventType type = EventType( stoi(keyval.substr(start, end - start)));
            int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
            EventInfo eventInfo;
            eventInfo.key_code_ = code;
            bind->BindEvent(type, eventInfo);
        }
        
        if (!AddBinding(bind)){
            delete bind;
        }
        
        bind = nullptr;
    }
    
    bindings.close();
}
