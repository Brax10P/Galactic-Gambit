#ifndef HOWTO_H
#define HOWTO_H
#include "states.h"
#include "button.h"

class HowTo
{
public:
    HowTo();
    State handleInput(sf::Event& e,  sf::RenderWindow& mWindow);
    void update();
    void render(sf::RenderWindow& mWindow);


private:
    sf::Font mFont;
    sf::Text mRules;
    sf::Text mValues;
    sf::RectangleShape mBackDrop;
    Button mBack; 
    sf::Texture mBackground;
};

#endif