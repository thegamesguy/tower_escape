//
//  Window.hpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

//#include <SFML/Graphics.hpp>
#include "EventManager.hpp"
//#include <stdio.h>

class Window {

public:
    Window();
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();
    
    void BeginDraw(); // Clear window.
    void EndDraw(); // Display changes.
    
    void Update();
    
    bool IsDone();
    bool IsFullscreen();
    bool IsFocused();
    
    sf::Vector2u GetWindowSize();
    EventManager* GetEventManager();
    
    void ToggleFullscreen(EventDetails * details = nullptr);
    void Close(EventDetails* details = nullptr);
    
    void Draw(sf::Drawable& drawable);
    
private:
    void Setup(const std::string title, const sf::Vector2u& size);
    void Destroy();
    void Create();
    
    EventManager event_manager_;
    sf::RenderWindow window_;
    sf::Vector2u window_size_;
    std::string window_title_;
    bool is_done_;
    bool is_fullscreen_;
    bool is_focused_;
};

#endif /* Window_hpp */
