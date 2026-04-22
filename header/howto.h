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
    sf::Text mRules;
    sf::Text mValues;
    sf::RectangleShape mBackDrop;
    sf::Font mFont;
    Button mBack; 
    sf::Texture mBackground;
};

#endif