#ifndef PLAY_H
#define PLAY_H
#include "states.h"
#include "button.h"
//#include "cherry.h"

// enum for calling different alien emotes
enum alienheadstate
{
    happy, smug, angry,
    neutral, laugh, blush,
    jackpot, tearsJoy, tearsSad
};


class Play
{
public:
    // legacy code
    Play();
    State handleInput(sf::Event& e,  sf::RenderWindow& window);
    void update(double elapsedTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    // new code
    void setAlienHead(alienheadstate state);

private:
    //legacy code from cherry lab;
    Button mRestart;  
    Button mRules;
    Button mResults;
    Button mExit;
    sf::RectangleShape mFrame;
    
    //newly added code for galactic gambit
    sf::RectangleShape mBackDrop;
    sf::Texture mBackground;

    int mTileHeight;
    int mTileWidth;

    float mAlienBaseX;
    float mAlienBaseY;
   
    sf::Texture mAlienTexture;
    sf::Sprite mAlienHead;


};

#endif