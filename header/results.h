/**
 * @file results.h
 * @author Hayden, Felix, Braxton
 * @brief 
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef RESULTS_H
#define RESULTS_H

#include "button.h"
#include "states.h"
class Results
{
public:
    Results();
    State handleInput(sf::Event& e, sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);


private:
    sf::Font mFont;
    sf::Text mResults;
    Button mRules;
    Button mPlayAgain;  
    Button mLeave;
};

#endif