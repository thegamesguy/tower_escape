//
//  IntroState.cpp
//  tower_escape
//
//  Created by Robert Wells on 01/02/2017.
//  Copyright © 2017 The Games Guy. All rights reserved.
//

#include "IntroState.hpp"
#include "StateManager.hpp"

IntroState::IntroState(StateManager& state_manager):BaseState(state_manager){}

IntroState::~IntroState(){}

void IntroState::OnCreate()
{
    time_passed_ = 0.0f;
    
    sf::Vector2u window_size = state_manager_.GetContext().window_->GetRenderWindow().getSize();
    
    intro_texture_background_.loadFromFile(resourcePath() + "country_back.png");
    
    intro_sprite_background_.setTexture(intro_texture_background_);
    intro_sprite_background_.setOrigin(intro_texture_background_.getSize().x * 0.5f, intro_texture_background_.getSize().y * 0.5f);
    intro_sprite_background_.setPosition(window_size.x * 0.5f, window_size.y * 0.5f);
    
    float target_scale_x = window_size.x / intro_sprite_background_.getLocalBounds().width;
    float target_scale_y = window_size.y / intro_sprite_background_.getLocalBounds().height;
    float target_scale = target_scale_x > target_scale_y ? target_scale_x :  target_scale_y;
    
    intro_sprite_background_.setScale(target_scale, target_scale);
    
    intro_texture_foreground_.loadFromFile(resourcePath() + "country_front.png");
    intro_sprite_foreground_.setTexture(intro_texture_foreground_);
    intro_sprite_foreground_.setOrigin(intro_texture_foreground_.getSize().x * 0.5f, intro_texture_foreground_.getSize().y * 0.5f);
    intro_sprite_foreground_.setPosition(window_size.x * 0.5f, window_size.y * 0.5f);
    intro_sprite_foreground_.setScale(target_scale, target_scale);
    
    intro_font_.loadFromFile(resourcePath() + "operational_amplifier.ttf");
    intro_text_.setFont(intro_font_);
    intro_text_.setString("Press SPACE to continue");
    intro_text_.setCharacterSize(30);
    sf::FloatRect text_rect = intro_text_.getLocalBounds();
    intro_text_.setOrigin(text_rect.left + text_rect.width * 0.5f, text_rect.top + text_rect.height * 0.5f);
    intro_text_.setPosition(window_size.x * 0.5f, window_size.y * 0.5f);
    intro_text_.setFillColor(sf::Color::Black);
    
    state_manager_.GetContext().event_manager_->AddCallback(StateType::kIntro, "intro_continue", &IntroState::Continue, this);
    
}

void IntroState::OnDestroy()
{
    state_manager_.GetContext().event_manager_->RemoveCallback(StateType::kIntro, "intro_continue");
}

void IntroState::Activate()
{
    
}

void IntroState::Deactivate()
{
    
}

void IntroState::Update(const sf::Time &time)
{
    time_passed_ += time.asSeconds();
}

void IntroState::Draw()
{
    Window* window = state_manager_.GetContext().window_;
    
    window->Draw(intro_sprite_background_);
    window->Draw(intro_sprite_foreground_);
    
    if(time_passed_ > 2.0f) {
        window->Draw(intro_text_);
    }
}

void IntroState::Continue(EventDetails *event_details)
{
    if(time_passed_ > 2.0f) {
        state_manager_.SwitchTo(StateType::kMainMenu);
        state_manager_.Remove(StateType::kIntro);
    }
}
