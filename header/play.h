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

    // chips tile variables
    int mChipsHeight;
    int mChipsWidth;

    // chip stack base offset variables
    float mMoon1OffsetX;
    float mMoon1OffsetY;

    float mVenus5OffsetX;
    float mVenus5OffsetY;

    float mEarth10OffsetX;
    float mEarth10OffsetY;

    float mMars20OffsetX;
    float mMars20OffsetY;

    float mSaturn50OffsetX;
    float mSaturn50OffsetY;

    float mNeptune100OffsetX;
    float mNeptune100OffsetY;

    float mAlienBaseX;
    float mAlienBaseY;

    float mChipsBaseX;
    float mChipsBaseY;

    int mMoon1;
    int mVenus5;
    int mEarth10;
    int mMars20;
    int mSaturn50;
    int mNeptune100;
   
    sf::Texture mAlienTexture;
    sf::Sprite mAlienHead;

    // individual chip stacks class variables
    sf::Texture mChipsTexture;
    sf::Sprite mMoon1Stack;

    sf::Sprite mVenus5Stack;

    
    sf::Sprite mEarth10Stack;

    sf::Sprite mMars20Stack;

    sf::Sprite mSaturn50Stack;

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