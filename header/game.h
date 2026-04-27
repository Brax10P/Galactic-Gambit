/**
 * @file game.h
 * @author Braxton, Hayden, & Felix
 * @brief header file for game
 * @version 0.1
 * @date 2026-04-06
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef GAME_H
#define GAME_H
#include "states.h"
#include "howto.h"
#include "welcome.h"
#include "play.h"
#include "results.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
using std::vector;

class Game
{
public:
    Game();
    ~Game(){};

    void handleInput(sf::RenderWindow& mWindow);
    void update(double elapsedTime, sf::RenderWindow& mWindow);
    void render(sf::RenderWindow& mWindow);
    //bool isDone() const;

private:
    //sf::RenderWindow mWindow;
    // bool mIsDone;
    State mGameState;
    Welcome mWelcomeScreen;
    Play mGame;
    Results mResults;
    HowTo mHowTo;
};

class Deck
{
public:
    Deck();
    void setupDeck();       // - set the deck up using cardSprite and cardValue
    void loadcardSprites(); // - load card sprites from sprite sheet

private:
    vector<sf::RectangleShape> cardSprites; // - Used to hold the card sprites
    vector<int> cardValue;  // - holds the card's value based on the card
    sf::Texture cardSpriteSheet;
};

#endif
