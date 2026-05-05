/**
 * @file welcome.h
 * @author Braxton, Felix, Hayden
 * @brief header file for welcome screen 
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef WELCOME_H
#define WELCOME_H
#include "states.h"
#include "button.h"

class Welcome
{
public:
    Welcome();
    State handleInput(sf::Event& e,  sf::RenderWindow& mWindow);
    void update();
    void render(sf::RenderWindow& mWindow);


private:
    sf::Font mFont;
    sf::Text mRules;
    sf::Text mHeader;
    Button mStart; 
    Button mHowTo; 
    sf::Texture mBackground;
    sf::Sprite mBackDrop;
};

#endif