/**
 * @file play.h
 * @author Hayden, Felix, Braxton
 * @brief header file that encompasses all elements, functions, and assets coded or loaded for galactic gambit gameplay
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */
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

// enum for calling different alien emotes
enum alienheadstate
{
    happy, smug, angry,
    neutral, laugh, blush,
    jackpot, tearsJoy, tearsSad
};

/**
 * @brief General play class that handles all functions and elements related to the gameplay of galactic gambit
 * 
 */
class Play
{
public:
    // legacy code from cherry lab
    Play();
    State handleInput(sf::Event& e,  sf::RenderWindow& window);
    void update(double elapsedTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    // new code written for galactic gambit
    void setAlienHead(alienheadstate state);

    void setChipStacks(int clickedChip);
    void displayChipStacks();

    // code down here to do with the deck and cards
    void dealPlayerHand();
    void dealDealerHand();

    void setupDeck();       // - set the deck up using cardSprite and cardValue
    void loadcardSprites(); // - load card sprites from sprite sheet
    void drawAnotherCard();
    void dealerTurn();
    void drawDealerCard();
    void resetGame();
    bool shouldReturnToWelcome() const {return mReturnToWelcome;}

    // FOR TESTS
    // testing getters
    int getPlayerMoney() const { return mPlayerMoney; }
    int getCurrentBet() const { return mCurrentBet; }
    int getPlayerScore() const { return mPlayerScore; }
    int getDealerScore() const { return mDealerScore; }
    int getPlayerCardCount() const { return mPlayerCardCount; }
    bool getBettingPhase() const { return mBettingPhase; }
    bool getRoundOver() const { return mRoundOver; }
    std::string getResultMessage() const { return mResultMessage; }
    int getDeckSize() const { return cardValue.size(); }
    void setDeckForTest(const vector<int>& testDeck)
    {
        cardValue = testDeck;
    }
    sf::Vector2f getCardOnePosition() const { return mCardOne.getPosition(); }
    sf::Vector2f getCardTwoPosition() const { return mCardTwo.getPosition(); }
    sf::Vector2f getDealerCardOnePosition() const { return mDealerCardOne.getPosition(); }
    sf::Vector2f getDealerCardTwoPosition() const { return mDealerCardTwo.getPosition(); }


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
    // orignal offsets were infered based desired location, the individual display functions adjust offset manually
    // as was necessary
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

    // same concept as the chips above but for the alien head location
    // this is required as the head swaps based on game conditions
    float mAlienBaseX;
    float mAlienBaseY;

    float mChipsBaseX;
    float mChipsBaseY;

    // chip counter variables, each can reach a maximum of 5 due to how their functions are written
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

    bool mBustDelay;
    float mBustTimer;
    

    sf::Texture cardSpriteSheet;

    // deck cards/values
    vector<sf::Sprite> cardSprites; // - Used to hold the card sprites
    vector<int> cardValue;  // - holds the card's value based on the card
    // vector<sf::Sprite> cardDealerSprites;
    // vector<int> cardDealerValue;

    // Went with six cards displayable
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