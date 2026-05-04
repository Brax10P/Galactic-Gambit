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