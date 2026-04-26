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

    void setChipStacks(int clickedChip);
    void displayChipStacks();

private:
    //legacy code from cherry lab;
    Button mRestart;  
    Button mRules;
    Button mResults;
    Button mExit;
    sf::RectangleShape mFrame;
    
    // newly added code for galactic gambit
    sf::RectangleShape mBackDrop;
    sf::Texture mBackground;

    // alien head class variables
    int mTileHeight;
    int mTileWidth;

    float mAlienBaseX;
    float mAlienBaseY;

    int mMoon1;
    int mVenus5;
    int mEarth10;
    int mMars20;
    int mSaturn50;
    int mNeptune100;
   
    sf::Texture mAlienTexture;
    sf::Sprite mAlienHead;

    // individual chip stacks class variables
    sf::Texture mMoon1Texture;
    sf::Sprite mMoon1Stack;

    sf::Texture mVenus5Texture;
    sf::Sprite mVenus5Stack;

    sf::Texture mEarth10Texture;
    sf::Sprite mEarth10Stack;

    sf::Texture mMars20Texture;
    sf::Sprite mMars20Stack;

    sf::Texture mSaturn50Texture;
    sf::Sprite mSaturn50Stack;

    sf::Texture mNeptune100Texture;
    sf::Sprite mNeptune100Stack;

    //ufo buttons
    Button m1;
    Button m5;
    Button m10;
    Button m20;
    Button m50;
    Button m100;
    

};



#endif