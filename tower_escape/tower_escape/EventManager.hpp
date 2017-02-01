//
//  EventManager.hpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "EnumHash.hpp"

enum class EventType{
    kKeyDown = sf::Event::KeyPressed,
    kKeyUp = sf::Event::KeyReleased,
    kMButtonDown = sf::Event::MouseButtonPressed,
    kMButtonUp = sf::Event::MouseButtonReleased,
    kMouseWheel = sf::Event::MouseWheelMoved,
    kWindowResized = sf::Event::Resized,
    kGainedFocus = sf::Event::GainedFocus,
    kLostFocus = sf::Event::LostFocus,
    kMouseEntered = sf::Event::MouseEntered,
    kMouseLeft = sf::Event::MouseLeft,
    kClosed = sf::Event::Closed,
    kTextEntered = sf::Event::TextEntered,
    kKeyboard = sf::Event::Count + 1,     // Ensures all values past this point are greater than event enumeration.
    kMouse,
    kJoystick
};

// Binds event type and keycode.
struct EventInfo{
    EventInfo(){key_code_ = 0;}
    EventInfo(int event){key_code_ = event;}
    union {
        int key_code_;
    };
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails{
    EventDetails(const std::string& bind_name) : bind_name_(bind_name){}
    
    void Clear()
    {
        size_ = sf::Vector2i(0, 0);
        text_entered_ = 0;
        mouse_ = sf::Vector2i(0, 0);
        mouse_delta_ = 0;
        key_code_ = -1;
    }
    
    std::string bind_name_;
    sf::Vector2i size_;
    sf::Uint32 text_entered_;
    sf::Vector2i mouse_;
    int mouse_delta_;
    int key_code_;
};

struct Binding{
    Binding(const std::string& name) : name_(name), details_(name), event_count_(0){}
    
    void BindEvent(EventType event_type, EventInfo event_info = EventInfo())
    {
        events_.emplace_back(event_type, event_info);
    }
    
    Events events_;
    std::string name_;
    EventDetails details_;
    int event_count_;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;

using Callbacks = std::unordered_map<StateType, CallbackContainer, EnumClassHash>;

class EventManager{
public:
    EventManager();
    ~EventManager();
    
    bool AddBinding(Binding* binding);
    bool RemoveBinding(std::string binding_name);
    
    void SetFocus(const bool& focus);
    
    void HandleInput();
    void Update();
    
    template<class T> bool AddCallback(StateType state, const std::string name, void(T::*func)(EventDetails*), T*instance)
    {
        auto itr = callbacks_.emplace(state, CallbackContainer()).first;
        auto temp = std::bind(func, instance, std::placeholders::_1);
        return itr->second.emplace(name, temp).second;
    }
    
    bool RemoveCallback(StateType state, const std::string& name);
    
    sf::Vector2i GetMousePosition(sf::RenderWindow* window = nullptr);
    
    void HandleEvent(sf::Event& event);
    
private:
    void LoadBindings();
    
    Bindings bindings_;
    Callbacks callbacks_;
    StateType current_state_;
    bool has_focus_;
};

#endif /* EventManager_hpp */
