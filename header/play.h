#ifndef PLAY_H
#define PLAY_H
#include "states.h"
#include "button.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
using std::vector;
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

    // code down here to do with the deck and cards
    void dealPlayerHand();
    void dealDealerHand();

    void setupDeck();       // - set the deck up using cardSprite and cardValue
    // void setupDealerDeck();
    void loadcardSprites(); // - load card sprites from sprite sheet
    void drawAnotherCard();
    void dealerTurn();
    void drawDealerCard();
    void resetGame();
    bool shouldReturnToWelcome() const {return mReturnToWelcome;}

private:
    //legacy code from cherry lab;
    Button mRestart;  
    Button mResults;
    Button mExit;
    sf::RectangleShape mFrame;
    
    // newly added code for galactic gambit
    sf::Texture mBackground;
    sf::RectangleShape mBackDrop;

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

    //Blackjack buttons
    Button mHit;
    Button mStand;
    Button mDeal;

    //Blackjack logic
    bool mRoundOver;
    std::string mResultMessage;
    sf::Font mFont;
    sf::Text mResultText;
    sf::Text mMoneyText;
    sf::Text mBetText;
    sf::Text mPlayerScoreText;
    sf::Text mDealerScoreText;
    int mPlayerAces;
    int mDealerAces;
    bool mRevealDealerCards;
    sf::Texture mCardBackTexture;
    sf::Sprite mCardBack;
    bool mDealerDrawing;
    float mDealerDrawTimer;
    int mPlayerMoney;
    int mCurrentBet;
    bool mBettingPhase;
    bool mGameOverDelay;
    float mGameOverTimer;
    bool mReturnToWelcome;
    

    sf::Texture cardSpriteSheet;
    // deck cards/values
    vector<sf::Sprite> cardSprites; // - Used to hold the card sprites
    vector<int> cardValue;  // - holds the card's value based on the card
    // vector<sf::Sprite> cardDealerSprites;
    // vector<int> cardDealerValue;

    // Went with six JUST incase
    sf::Sprite mCardOne;
    sf::Sprite mCardTwo;
    sf::Sprite mCardThree;
    sf::Sprite mCardFour;
    sf::Sprite mCardFive;
    sf::Sprite mCardSix;

    // Specifically for the dealer cards
    sf::Sprite mDealerCardOne;
    sf::Sprite mDealerCardTwo;
    sf::Sprite mDealerCardThree;
    sf::Sprite mDealerCardFour;
    sf::Sprite mDealerCardFive;
    sf::Sprite mDealerCardSix;

    int mPlayerScore; // Add the values from "cardValue" / "cardDealerValue" vectors for overall score
    int mDealerScore;
    int mPlayerCardCount;
    int mDealerCardCount;

};


#endif