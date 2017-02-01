//
//  StateManager.hpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef StateManager_hpp
#define StateManager_hpp


#include "Window.hpp"
#include "BaseState.hpp"
#include <unordered_map>

enum class StateType {
    kIntro = 1,
    kMainMenu,
    kGame,
    kPaused,
    kGameOver,
    kCredits
};



struct SharedContext {
    SharedContext():window_(nullptr), event_manager_(nullptr){}
    
    Window* window_;
    EventManager* event_manager_;
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;


class StateManager {
public:
    StateManager(SharedContext& context);
    ~StateManager();
    
    void Update(const sf::Time& time);
    void Draw();
    
    void ProcessRequests();
    
    SharedContext& GetContext();
    bool HasState(const StateType& state_type);
    
    void SwitchTo(const StateType& state_type);
    void Remove(const StateType& state_type);
    
private:
    void CreateState(const StateType& state_type);
    void RemoveState(const StateType& state_type);
    
    template<class T>
    void RegisterState(const StateType& state_type) {
        state_factory_[state_type] = [this]()->BaseState*
        {
            return new T(this);
        };
    }
    
    
    SharedContext& shared_context_;
    StateContainer states_;
    TypeContainer states_to_remove_;
    std::unordered_map<StateType, std::function<BaseState*(void)>, EnumClassHash> state_factory_;
};

#endif /* StateManager_hpp */
