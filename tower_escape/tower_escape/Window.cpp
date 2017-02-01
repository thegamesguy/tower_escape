//
//  Window.cpp
//  tower_escape
//
//  Created by Robert Wells on 31/01/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "Window.hpp"
#include "StateManager.hpp"

Window::Window()
{
    Setup("Untitled Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size)
{
    Setup(title, size);
}

Window::~Window()
{
    Destroy();
}

void Window::Setup(const std::string title, const sf::Vector2u& size)
{
    //window_icon_.loadFromFile(resourcePath() + "icon.png");
    
    //window_.setIcon(window_icon_.getSize().x, window_icon_.getSize().y, window_icon_.getPixelsPtr());
    
    window_title_ = title;
    initial_window_size_ = size;
    is_fullscreen_ = false;
    is_done_ = false;
    is_focused_ = true;
    

    // Global states callbacks.
    event_manager_.AddCallback(StateType(0), "fullscreen_toggle", &Window::ToggleFullscreen, this);
    event_manager_.AddCallback(StateType(0), "window_close", &Window::Close, this);
    
    Create();
}

void Window::Create()
{
    sf::Uint32 style = is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
    
    window_.create({initial_window_size_.x, initial_window_size_.y, 32}, window_title_, style);
}

void Window::Destroy()
{
    window_.close(); // Destroys all associated resources.
}

void Window::Update()
{
    sf::Event event;
    
    while(window_.pollEvent(event)) {
        if(event.type == sf::Event::LostFocus) {
            is_focused_ = false;
            event_manager_.SetFocus(is_focused_);
        } else if(event.type == sf::Event::GainedFocus) {
            is_focused_ = true;
            event_manager_.SetFocus(is_focused_);
        }
        event_manager_.HandleEvent(event);
    }
    
    event_manager_.Update();
}

void Window::ToggleFullscreen(EventDetails* details)
{
    is_fullscreen_ = !is_fullscreen_;
    Destroy();
    Create();
}

void Window::Close(EventDetails* details)
{
    is_done_ = true;
}

void Window::BeginDraw()
{
    window_.clear(sf::Color::Black);
}

void Window::EndDraw()
{
    window_.display();
}

bool Window::IsDone()
{
    return is_done_;
}

bool Window::IsFullscreen()
{
    return is_fullscreen_;
}

/*
sf::Vector2u Window::GetWindowSize()
{
    return window_size_;
}
 */

sf::RenderWindow& Window::GetRenderWindow()
{
    return window_;
}

void Window::Draw(sf::Drawable& drawable)
{
    window_.draw(drawable);
}

EventManager* Window::GetEventManager()
{
    return &event_manager_;
}





