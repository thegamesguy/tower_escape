//
//  BaseState.hpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef BaseState_hpp
#define BaseState_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class StateManager;


class BaseState {
    //friend class StateManager;
    
public:
    BaseState(StateManager& state_manager) : state_manager_(state_manager),
    is_transparent_(false), is_transcendent_(false){}
    virtual ~BaseState();
    
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    
    virtual void Update(const sf::Time& time) = 0;
    virtual void Draw() = 0;
    
    void SetTransparent(bool transparent)
    {
        is_transparent_ = transparent;
    }
    bool IsTransparent()
    {
        return is_transparent_;
    }
    
    void SetTranscendent(bool transcendent)
    {
        is_transcendent_ = transcendent;
    }
    bool IsTranscendent()
    {
        return is_transcendent_;
    }
    
    StateManager& GetStateManager()
    {
        return state_manager_;
    }
    
protected:
    StateManager& state_manager_;
    bool is_transparent_;
    bool is_transcendent_;
};

#endif /* BaseState_hpp */
