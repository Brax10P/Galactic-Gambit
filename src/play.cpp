#include "../header/play.h"
Play::Play()
{
    // new code for galctic game background
    mBackDrop.setSize(sf::Vector2f(1280.f, 720.f));
    if (!mBackground.loadFromFile("assets/game screen/Poker in outer space.png"))
    {
        std::cout << "Error opening background file\n";
        exit(2);
    }
    mBackDrop.setTexture(&mBackground);

    if (!mAlienTexture.loadFromFile("assets/game screen/Alien emoticons in astronaut helmets.png"))
    {
        std::cout << "Error opening alien head file\n";
        exit(2);
    }

    if (!mChipsTexture.loadFromFile("assets/game screen/chip stacks png.png"))
    {
        std::cout << "Error opening chip stack image file\n";
        exit(2);
    }

    mRevealDealerCards = false;

    if (!mCardBackTexture.loadFromFile("assets/game screen/card back.png"))
    {
        std::cout << "Error opening card back file\n";
        exit(2);
    }

    //For the hidden dealer card
    mCardBack.setTexture(mCardBackTexture);
    mCardBack.setTextureRect(sf::IntRect(200, 120, 240, 300));
    mCardBack.setOrigin((5.f), (8.f));
    mCardBack.setScale(1.55f, 1.55f);
    mCardBack.setPosition({420, 182});

    if (!mFont.loadFromFile("assets/VintageCharm-Regular.otf"))
    {
        std::cout << "Error loading font\n";
        exit(2);
    }

    //Code for setting the in game text (results, money, betsize, card scores)
    mResultText.setFont(mFont);
    mResultText.setCharacterSize(40);
    mResultText.setFillColor(sf::Color::White);
    mResultText.setPosition({700, 375});

    mMoneyText.setFont(mFont);
    mMoneyText.setCharacterSize(32);
    mMoneyText.setFillColor(sf::Color::White);
    mMoneyText.setPosition({1000.f, 20.f});

    mBetText.setFont(mFont);
    mBetText.setCharacterSize(32);
    mBetText.setFillColor(sf::Color::White);
    mBetText.setPosition({1000.f, 60.f});

    mPlayerScoreText.setFont(mFont);
    mPlayerScoreText.setCharacterSize(32);
    mPlayerScoreText.setFillColor(sf::Color::White);
    mPlayerScoreText.setPosition({400.f, 500.f});

    mDealerScoreText.setFont(mFont);
    mDealerScoreText.setCharacterSize(32);
    mDealerScoreText.setFillColor(sf::Color::White);
    mDealerScoreText.setPosition({400.f, 325.f});

    //initializes all the blackjack logic 
    mPlayerScore = 0;
    mDealerScore = 0;
    mPlayerAces = 0;
    mDealerAces = 0;
    mRoundOver = false;
    mResultMessage = "";
    mDealerDrawing = false;
    mDealerDrawTimer = 0.f;
    mPlayerMoney = 500;
    mCurrentBet = 0;
    mBettingPhase = true;
    mGameOverDelay = false;
    mGameOverTimer = 0.f;
    mReturnToWelcome = false;

    // UFO buttons
    m1.setTexturePaths("assets/game screen/ufonormal.png", "assets/game screen/ufohovered.png");
    m1.setText("");
    m1.setPosition({190, 555});
    m1.setSize({200, 200});

    m5.setTexturePaths("assets/game screen/ufonormal.png", "assets/game screen/ufohovered.png");
    m5.setText("");
    m5.setPosition({366, 555});
    m5.setSize({200, 200});

    m10.setTexturePaths("assets/game screen/ufonormal.png", "assets/game screen/ufohovered.png");
    m10.setText("");
    m10.setPosition({542, 555});
    m10.setSize({200, 200});

    m20.setTexturePaths("assets/game screen/ufonormal.png", "assets/game screen/ufohovered.png");
    m20.setText("");
    m20.setPosition({718, 555});
    m20.setSize({200, 200});

    m50.setTexturePaths("assets/game screen/ufonormal.png", "assets/game screen/ufohovered.png");
    m50.setText("");
    m50.setPosition({894, 555});
    m50.setSize({200, 200});

    m100.setTexturePaths("assets/game screen/ufonormal.png", "assets/game screen/ufohovered.png");
    m100.setText("");
    m100.setPosition({1070, 555});
    m100.setSize({200, 200});

    // Blackjack buttons
    mHit.setText("Hit");
    mHit.setPosition({100, 100});
    mHit.setSize({150, 150});
    mHit.setColorTextNormal(sf::Color::Blue);

    mStand.setText("Stand");
    mStand.setPosition({100, 275});
    mStand.setSize({150, 150});
    mStand.setColorTextNormal(sf::Color::Blue);

    mDeal.setText("Deal Now");
    mDeal.setPosition({640, 375});
    mDeal.setSize({150, 150});
    mDeal.setColorTextNormal(sf::Color::Blue);

    setupDeck();
    mPlayerCardCount = 0;
    mDealerCardCount = 0;

    // attaches texture to sprite
    mAlienHead.setTexture(mAlienTexture);

    // gets image size
    sf::Vector2u size = mAlienTexture.getSize();

    // calculate tile size so we dont have to manually pinpoint each heads pixels (3x3 grid)
    mTileWidth = size.x / 3;
    mTileHeight = size.y / 3;

    // center origin for more intuitive adjustments
    mAlienHead.setOrigin(mTileWidth / 2.f, mTileHeight / 2.f);

    // position of head on screen, these cordinates are specific to neutral
    // mAlienHead.setPosition(590.f, 125.f);
    mAlienBaseX = 590.f;
    mAlienBaseY = 125.f;

    // scaler if needed
    mAlienHead.setScale(0.65f, 0.65f);

    // sets starting expression
    setAlienHead(neutral);

    // code below here for setting base chip stack stuff

    // each chip stack sprite is changed by shifting the texture over to the next stack thus incrementing 1 chip at a time
    // attaches textures to sprites
    mMoon1Stack.setTexture(mChipsTexture);
    mVenus5Stack.setTexture(mChipsTexture);
    mEarth10Stack.setTexture(mChipsTexture);
    mMars20Stack.setTexture(mChipsTexture);
    mSaturn50Stack.setTexture(mChipsTexture);
    mNeptune100Stack.setTexture(mChipsTexture);

    // some chips were rescaling for some reason, this is my attempt to force them to not do that
    mMoon1Stack.setScale(1.f, 1.f);
    mVenus5Stack.setScale(1.f, 1.f);
    mEarth10Stack.setScale(1.f, 1.f);
    mMars20Stack.setScale(1.f, 1.f);
    mSaturn50Stack.setScale(1.f, 1.f);
    mNeptune100Stack.setScale(1.f, 1.f);

    // Initializes chip counters
    mMoon1 = 0;
    mVenus5 = 0;
    mEarth10 = 0;
    mMars20 = 0;
    mSaturn50 = 0;
    mNeptune100 = 0;

    // Initializes tile size for chip stacks
    mChipsWidth = 128;
    mChipsHeight = 80;

    // Base position where all chip stacks will be placed realtive from
    mChipsBaseX = 10.f;
    mChipsBaseY = 500.f;

    // Base offsets, not sure if ill modify here or in the function to line everything up
    mMoon1OffsetX = 0.f;
    mMoon1OffsetY = 0.f;

    mVenus5OffsetX = 75.f;
    mVenus5OffsetY = 7.f;

    mEarth10OffsetX = 2.f;
    mEarth10OffsetY = -50.f;

    mMars20OffsetX = 77.f;
    mMars20OffsetY = -48.f;

    mSaturn50OffsetX = 7.f;
    mSaturn50OffsetY = -115.f;

    mNeptune100OffsetX = 84.f;
    mNeptune100OffsetY = -115.f;

    displayChipStacks();

}

State Play::handleInput(sf::Event &e, sf::RenderWindow &window)
{
    //if player money runs out
    if (mPlayerMoney <= 0)
    {
        //changes the alien head and text, sets delay 
        if (!mGameOverDelay)
        {
            mResultMessage = "You're out of money!";
            setAlienHead(tearsSad);

            mGameOverDelay = true;
            mGameOverTimer = 0.f;
        }

        return game;
    }

    //code for betting phase (click UFOS, money goes in)
    if (mBettingPhase && !mRoundOver && !mDealerDrawing && m1.handleInput(e, window))
    {
        mCurrentBet += 1;
        setChipStacks(1);
    }

    if (mBettingPhase && !mRoundOver && !mDealerDrawing && m5.handleInput(e, window))
    {
        mCurrentBet += 5;
        setChipStacks(5);
    }

    if (mBettingPhase && !mRoundOver && !mDealerDrawing && m10.handleInput(e, window))
    {
        mCurrentBet += 10;
        setChipStacks(10);
    }

    if (mBettingPhase && !mRoundOver && !mDealerDrawing && m20.handleInput(e, window))
    {
        mCurrentBet += 20;
        setChipStacks(20);
    }

    if (mBettingPhase && !mRoundOver && !mDealerDrawing && m50.handleInput(e, window))
    {
        mCurrentBet += 50;
        setChipStacks(50);
    }

    if (mBettingPhase && !mRoundOver && !mDealerDrawing && m100.handleInput(e, window))
    {
        mCurrentBet += 100;
        setChipStacks(100);
    }

    //if there is at least $1 bet and user clicks deal button
    if (mBettingPhase && mCurrentBet > 0 && mDeal.handleInput(e, window))
    {
        mBettingPhase = false;

        mPlayerScore = 0;
        mDealerScore = 0;
        mPlayerAces = 0;
        mDealerAces = 0;

        mRevealDealerCards = false;
        mRoundOver = false;
        mResultMessage = "";
        setAlienHead(neutral);

        mPlayerCardCount = 2;
        mDealerCardCount = 2;

        //had to initialize other cards to blank sprites to prevent 3 cards being dealt
        //on the start of round 2
        mCardOne = sf::Sprite();
        mCardTwo = sf::Sprite();
        mCardThree = sf::Sprite();
        mCardFour = sf::Sprite();
        mCardFive = sf::Sprite();
        mCardSix = sf::Sprite();

        mDealerCardOne = sf::Sprite();
        mDealerCardTwo = sf::Sprite();
        mDealerCardThree = sf::Sprite();
        mDealerCardFour = sf::Sprite();
        mDealerCardFive = sf::Sprite();
        mDealerCardSix = sf::Sprite();

        dealPlayerHand();
        dealDealerHand();
    }

    //if the user presses hit
    if (!mBettingPhase && !mRoundOver && !mDealerDrawing && mHit.handleInput(e, window))
    {
        mBettingPhase = false;
        drawAnotherCard();

        //if player busts
        if (mPlayerScore > 21)
        {
            mResultMessage = "Player busts!";
            mPlayerMoney -= mCurrentBet;
            mRoundOver = true;
            mCurrentBet = 0;
            mMoon1 = 0;
            mVenus5 = 0;
            mEarth10 = 0;
            mMars20 = 0;
            mSaturn50 = 0;
            mNeptune100 = 0;
            displayChipStacks();
            mBettingPhase = true;
            mRoundOver = false;
            setAlienHead(laugh);
        }
    }

    //if stand, dealers turn
    if (!mBettingPhase && !mRoundOver && !mDealerDrawing && mStand.handleInput(e, window))
    {
        mBettingPhase = false;
        dealerTurn();
    }

    return game;
}
void Play::update(double elapsedTime, sf::RenderWindow &window)
{
    //if game over delay is set, starts tracking time
    if (mGameOverDelay)
    {
        mGameOverTimer += elapsedTime;
        mResultText.setString(mResultMessage);
        mMoneyText.setString("Money: $" + std::to_string(mPlayerMoney));

        //once it hits 2 seconds, returns to welcome screen
        if (mGameOverTimer >= 2.0f)
        {
            mGameOverDelay = false;
            mPlayerMoney = 0;
            mReturnToWelcome = true;
        }

        return;
    }
    
    //slight delay for dealer drawing cards so it looks better
    if (mDealerDrawing)
    {
        mDealerDrawTimer += elapsedTime;

        //one second delay, logic for dealer drawing below
        if (mDealerDrawTimer >= 1.0f)
        {
            if (mDealerScore < 17)
            {
                drawDealerCard();
                mDealerDrawTimer = 0.f;
            }
            else
            {
                if (mDealerScore > 21)
                {
                    mResultMessage = "Dealer busts! You win!";
                    mPlayerMoney += mCurrentBet;
                    setAlienHead(angry);
                }
                else if (mPlayerScore > mDealerScore)
                {
                    mResultMessage = "You win!";
                    mPlayerMoney += mCurrentBet;
                    setAlienHead(tearsSad);
                }
                else if (mPlayerScore < mDealerScore)
                {
                    mResultMessage = "Dealer wins!";
                    mPlayerMoney -= mCurrentBet;
                    setAlienHead(happy);
                }
                else if (mPlayerScore == 21)
                {
                    mResultMessage = "BlackJack!";
                    mPlayerMoney += mCurrentBet * 1.5;
                    setAlienHead(jackpot);
                }
                else
                {
                    mResultMessage = "Push!";
                }

                //re-initialize game loop stuff
                mRoundOver = true;
                mDealerDrawing = false;
                mCurrentBet = 0;
                mMoon1 = 0;
                mVenus5 = 0;
                mEarth10 = 0;
                mMars20 = 0;
                mSaturn50 = 0;
                mNeptune100 = 0;
                displayChipStacks();
                mBettingPhase = true;
                mRoundOver = false;
            }
        }
    }

    //updates player score cards
    mPlayerScoreText.setString("Player: " + std::to_string(mPlayerScore));

    //updates dealer score cards depending on if it is dealers turn or not
    if (!mRevealDealerCards)
    {
        mDealerScoreText.setString("Dealer: ?");
    }
    else
    {
        mDealerScoreText.setString("Dealer: " + std::to_string(mDealerScore));
    }
    //update logic for everything else
    m1.update();
    m5.update();
    m10.update();
    m20.update();
    m50.update();
    m100.update();
    mHit.update();
    mStand.update();
    mDeal.update();
    mMoneyText.setString("Money: $" + std::to_string(mPlayerMoney));
    mBetText.setString("Bet: $" + std::to_string(mCurrentBet));
    mResultText.setString(mResultMessage);
    mRestart.update();
    mResults.update();
    mExit.update();
}
void Play::render(sf::RenderWindow &window)
{
    // new code for galactic
    window.draw(mBackDrop);
    //draws UFO buttons when time to bet
    if (mBettingPhase)
    {
        window.draw(m1);
        window.draw(m5);
        window.draw(m10);
        window.draw(m20);
        window.draw(m50);
        window.draw(m100);
        window.draw(mDeal);
    }
    //draws cards and scores when betting ends
    if (!mBettingPhase)
    {
        window.draw(mHit);
        window.draw(mStand);
        window.draw(mCardOne);
        window.draw(mCardTwo);
        window.draw(mCardThree);
        window.draw(mCardFour);
        window.draw(mCardFive);
        window.draw(mCardSix);
        window.draw(mPlayerScoreText);
        window.draw(mDealerScoreText);
        if (!mRevealDealerCards)
        {
            window.draw(mCardBack);
            window.draw(mDealerCardTwo);
        }
        else
        {
            window.draw(mDealerCardOne);
            window.draw(mDealerCardTwo);
        }
        window.draw(mDealerCardThree);
        window.draw(mDealerCardFour);
        window.draw(mDealerCardFive);
        window.draw(mDealerCardSix);
    }
    //draws alien and money related texts
    window.draw(mResultText);
    window.draw(mMoneyText);
    window.draw(mBetText);
    window.draw(mAlienHead);

    // chip stack function is written in a way where tiles are only intentionally defined if the chip counter is > 0
    // these if statments prevent the program from setting the individual chip objects with the entire chip stack png
    if (mMoon1 != 0)
        window.draw(mMoon1Stack);

    if (mVenus5 != 0)
        window.draw(mVenus5Stack);

    if (mEarth10 != 0)
        window.draw(mEarth10Stack);

    if (mMars20 != 0)
        window.draw(mMars20Stack);

    if (mSaturn50 != 0)
        window.draw(mSaturn50Stack);

    if (mNeptune100 != 0)
        window.draw(mNeptune100Stack);
}
/**
 * @brief function for setting alien emote based on different conditions
 *
 * @param state
 */
void Play::setAlienHead(alienheadstate state)
{
    int w = mTileWidth;
    int h = mTileHeight;

    float x = mAlienBaseX;
    float y = mAlienBaseY;

    switch (state)
    {
    case happy:
        mAlienHead.setTextureRect(sf::IntRect(0, 0, w, h));
        mAlienHead.setPosition(x, y - 15.f);
        break;

    case smug:
        mAlienHead.setTextureRect(sf::IntRect(w, 0, w, h));
        mAlienHead.setPosition(x + 47.f, y - 15.f);
        break;

    case angry:
        mAlienHead.setTextureRect(sf::IntRect(2 * w, 0, w, h));
        mAlienHead.setPosition(x + 86.f, y - 17.f);
        break;

    case neutral:
        mAlienHead.setTextureRect(sf::IntRect(0, h, w, h));
        mAlienHead.setPosition(x, y);
        break;

    case laugh:
        mAlienHead.setTextureRect(sf::IntRect(w, h, w, h));
        mAlienHead.setPosition(x + 45.f, y);
        break;

    case blush:
        mAlienHead.setTextureRect(sf::IntRect(2 * w, h, w, h));
        mAlienHead.setPosition(x + 85.f, y - 3.f);
        break;

    case jackpot:
        mAlienHead.setTextureRect(sf::IntRect(0, 2 * h, w, h));
        mAlienHead.setPosition(x, y + 12.f);
        break;

    case tearsJoy:
        mAlienHead.setTextureRect(sf::IntRect(w, 2 * h, w, h));
        mAlienHead.setPosition(x + 42.f, y + 10.f);
        break;

    case tearsSad:
        mAlienHead.setTextureRect(sf::IntRect(2 * w, 2 * h, w, h));
        mAlienHead.setPosition(x + 83.f, y + 10.f);
        break;
    }
}
/**
 * @brief increments chip counter and calls displaychipStacks based on clickedChip which should be an int passed to this function when
 *        a chip denomination is clicked on the game screen
 *
 * @param clickedChip
 */
void Play::setChipStacks(int clickedChip)
{

    if (clickedChip == 1)
    {
        if (mMoon1 < 5)
        {
            mMoon1++;
            displayChipStacks();
        }
        else
            displayChipStacks();
    }
    if (clickedChip == 5)
    {
        if (mVenus5 < 5)
        {
            mVenus5++;
            displayChipStacks();
        }
        else
            displayChipStacks();
    }
    if (clickedChip == 10)
    {
        if (mEarth10 < 5)
        {
            mEarth10++;
            displayChipStacks();
        }
        else
            displayChipStacks();
    }
    if (clickedChip == 20)
    {
        if (mMars20 < 5)
        {
            mMars20++;
            displayChipStacks();
        }
        else
            displayChipStacks();
    }
    if (clickedChip == 50)
    {
        if (mSaturn50 < 5)
        {
            mSaturn50++;
            displayChipStacks();
        }
        else
            displayChipStacks();
    }
    if (clickedChip == 100)
    {
        if (mNeptune100 < 5)
        {
            mNeptune100++;
            displayChipStacks();
        }
        else
            displayChipStacks();
    }
}
/**
 * @brief breaks up chip stack png into tiles, takes values of all chip counters and displays appropriate chip texture for each
 *        some specific chip stacks required manual adjustment (a lot of the 5 stacks for hwatever reason) uses base offsets
 *        from constructor as a starting point then aproximates tiles based on image size.
 *
 */
void Play::displayChipStacks()
{
    sf::Vector2u size = mChipsTexture.getSize();

    int cellW = size.x / 5; // distance from one stack column to the next
    int cellH = size.y / 6; // distance from one chip type row to the next

    int cropW = 80; // actual chip stack image width
    int cropH = 80; // actual chip stack image height

    float x = mChipsBaseX;
    float y = mChipsBaseY;

    if (mMoon1 != 0)
    {
        mMoon1 = 1;
        mMoon1Stack.setTextureRect(sf::IntRect((mMoon1 - 1) * cellW + 5, 0 * cellH, cropW, cropH));

        mMoon1Stack.setPosition(x + mMoon1OffsetX, y + mMoon1OffsetY);
    }

    if (mVenus5 != 0)
    {
        if (mVenus5 == 5)
        {
            mVenus5Stack.setTextureRect(sf::IntRect((mVenus5 - 1) * cellW + 10, 1 * cellH + 3, cropW, cropH - 5));
            mVenus5Stack.setPosition(x + mVenus5OffsetX, y + mVenus5OffsetY);
        }
        else
        {
            mVenus5Stack.setTextureRect(sf::IntRect((mVenus5 - 1) * cellW, 1 * cellH, cropW, cropH));
            mVenus5Stack.setPosition(x + mVenus5OffsetX, y + mVenus5OffsetY);
        }
    }

    if (mEarth10 != 0)
    {
        if (mEarth10 == 5)
        {
            mEarth10Stack.setTextureRect(sf::IntRect((mEarth10 - 1) * cellW, 2 * cellH - 5, cropW + 10, cropH - 5));
            mEarth10Stack.setPosition(x + mEarth10OffsetX, y + mEarth10OffsetY);
        }
        else
        {
            mEarth10Stack.setTextureRect(sf::IntRect((mEarth10 - 1) * cellW, 2 * cellH - 5, cropW, cropH - 5));
            mEarth10Stack.setPosition(x + mEarth10OffsetX, y + mEarth10OffsetY);
        }
    }

    if (mMars20 != 0)
    {
        mMars20Stack.setTextureRect(sf::IntRect((mMars20 - 1) * cellW, 3 * cellH - 10, cropW + 5, cropH));
        mMars20Stack.setPosition(x + mMars20OffsetX, y + mMars20OffsetY);
    }

    if (mSaturn50 != 0)
    {

        if (mSaturn50 == 5)
        {
            mSaturn50Stack.setTextureRect(sf::IntRect((mSaturn50 - 1) * cellW + 10, 4 * cellH - 10, cropW, cropH));
            mSaturn50Stack.setPosition(x + mSaturn50OffsetX, y + mSaturn50OffsetY);
        }
        else
        {
            mSaturn50Stack.setTextureRect(sf::IntRect((mSaturn50 - 1) * cellW, 4 * cellH - 10, cropW, cropH));
            mSaturn50Stack.setPosition(x + mSaturn50OffsetX, y + mSaturn50OffsetY);
        }
    }

    if (mNeptune100 != 0)
    {

        if (mNeptune100 == 5)
        {
            mNeptune100Stack.setTextureRect(sf::IntRect((mNeptune100 - 1) * cellW, 5 * cellH - 2, cropW + 10, cropH + 2));

            mNeptune100Stack.setPosition(x + mNeptune100OffsetX - 10, y + mNeptune100OffsetY - 3);
        }
        else
        {
            mNeptune100Stack.setTextureRect(sf::IntRect((mNeptune100 - 1) * cellW, 5 * cellH - 2, cropW, cropH + 2));

            mNeptune100Stack.setPosition(x + mNeptune100OffsetX, y + mNeptune100OffsetY);
        }
    }
}

void Play::setupDeck()
{
    unsigned deckShuffle = std::chrono::system_clock::now().time_since_epoch().count();
    // Pretty much this will randomize the deck using
    // the time in miliseconds as a seed
    // mainly used this to be able to keep the shuffle
    // the exact same for both so a 2 card doesn't end up with 11

    cardValue = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    // First line is first suite, second is second suite, so on so forth

    loadcardSprites();

    shuffle(cardValue.begin(), cardValue.end(), std::default_random_engine(deckShuffle));
    shuffle(cardSprites.begin(), cardSprites.end(), std::default_random_engine(deckShuffle));
}



void Play::loadcardSprites()
{
    // section out cards from sprite sheet and store them in cardSprite vector
    cardSpriteSheet.loadFromFile("assets/galactic_gambit_cards.png");

    // These two are for adding the difference in the for loops
    // just added them here for simplicity sake, if we want to make them
    // private variables that is an option as well
    int xDiff = 0;

    // for loops below loading in one line, jumping to next, loading in next
    // there is a 41 pixel difference between each card horizontally
    for (int j = 0; j < 13; j++) // clubs being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (16), (40), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        // cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }

    xDiff = 0;

    for (int j = 0; j < 13; j++) // hearts being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (68), (40), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        // cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }

    xDiff = 0;

    for (int j = 0; j < 13; j++) // spades being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (121), (40), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        // cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }

    xDiff = 0;

    for (int j = 0; j < 13; j++) // diamonds being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (173), (43), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        // cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }
}

/**
 * @brief deals the player hand and handles ace logic
 * 
 */
void Play::dealPlayerHand()
{
    //sets player score to card value
    mPlayerScore += cardValue.back();
    int value = cardValue.back();
    //ace logic so aces can be 1 or 11
    if (value == 11)
    {
        mPlayerAces++;
    }
    while (mPlayerScore > 21 && mPlayerAces > 0)
    {
        mPlayerScore -= 10;
        mPlayerAces--;
    }
    cardValue.pop_back();
    //loads image of card to player card
    mCardOne = cardSprites.back();
    cardSprites.pop_back();
    mCardOne.setScale(2.0f, 2.0f);
    mCardOne.setPosition({575, 500});

    //same exact stuff for card 2
    mPlayerScore += cardValue.back();
    value = cardValue.back();
    if (value == 11)
    {
        mPlayerAces++;
    }
    while (mPlayerScore > 21 && mPlayerAces > 0)
    {
        mPlayerScore -= 10;
        mPlayerAces--;
    }
    cardValue.pop_back();
    mCardTwo = cardSprites.back();
    cardSprites.pop_back();
    mCardTwo.setScale(2.0f, 2.0f);
    mCardTwo.setPosition({650, 500});
}

/**
 * @brief deals the dealer cards, same exact logic as player hand
 * 
 */
void Play::dealDealerHand()
{
    mDealerScore += cardValue.back();
    int value = cardValue.back();
    if (value == 11)
    {
        mDealerAces++;
    }
    while (mDealerScore > 21 && mDealerAces > 0)
    {
        mDealerScore -= 10;
        mDealerAces--;
    }
    cardValue.pop_back();
    mDealerCardOne = cardSprites.back();
    cardSprites.pop_back();
    mDealerCardOne.setScale(2.0f, 2.0f);
    mDealerCardOne.setPosition({575, 325});

    mDealerScore += cardValue.back();
    value = cardValue.back();
    if (value == 11)
    {
        mDealerAces++;
    }
    while (mDealerScore > 21 && mDealerAces > 0)
    {
        mDealerScore -= 10;
        mDealerAces--;
    }
    cardValue.pop_back();
    mDealerCardTwo = cardSprites.back();
    cardSprites.pop_back();
    mDealerCardTwo.setScale(2.0f, 2.0f);
    mDealerCardTwo.setPosition({650, 325});
}

/**
 * @brief code for drawing one card at a time after the initial deal
 * similar to deal logic, slightly different for positioning
 * 
 */
void Play::drawAnotherCard()
{
    mPlayerScore += cardValue.back();
    int value = cardValue.back();
    if (value == 11)
    {
        mPlayerAces++;
    }
    while (mPlayerScore > 21 && mPlayerAces > 0)
    {
        mPlayerScore -= 10;
        mPlayerAces--;
    }
    cardValue.pop_back();

    //create a new card
    sf::Sprite newCard = cardSprites.back();
    cardSprites.pop_back();

    newCard.setScale(2.0f, 2.0f);
    //sets card based on # of cards already in hand
    newCard.setPosition({575.f + (75.f * mPlayerCardCount), 500.f});

    //determines which mCard to assign new card to based on how many cards person has in hand
    if (mPlayerCardCount == 2)
        mCardThree = newCard;
    else if (mPlayerCardCount == 3)
        mCardFour = newCard;
    else if (mPlayerCardCount == 4)
        mCardFive = newCard;
    else if (mPlayerCardCount == 5)
        mCardSix = newCard;

    mPlayerCardCount++;
}

/**
 * @brief dealer turn, reveal hidden card, set dealerdrawing, start timer for delay
 * 
 */
void Play::dealerTurn()
{
    mRevealDealerCards = true;
    mDealerDrawing = true;
    mDealerDrawTimer = 0.f;
}

/**
 * @brief draw dealer card, same logic as dealanothercard
 * 
 */
void Play::drawDealerCard()
{
    mDealerScore += cardValue.back();
    int value = cardValue.back();
    if (value == 11)
    {
        mDealerAces++;
    }
    while (mDealerScore > 21 && mDealerAces > 0)
    {
        mDealerScore -= 10;
        mDealerAces--;
    }
    cardValue.pop_back();

    sf::Sprite newCard = cardSprites.back();
    cardSprites.pop_back();

    newCard.setScale(2.0f, 2.0f);
    newCard.setPosition({575.f + (75.f * mDealerCardCount), 325.f});

    if (mDealerCardCount == 2)
        mDealerCardThree = newCard;
    else if (mDealerCardCount == 3)
        mDealerCardFour = newCard;
    else if (mDealerCardCount == 4)
        mDealerCardFive = newCard;
    else if (mDealerCardCount == 5)
        mDealerCardSix = newCard;

    mDealerCardCount++;
}

//reinitializes the logic variables 
void Play::resetGame()
{
    mPlayerMoney = 500;
    mCurrentBet = 0;
    mPlayerScore = 0;
    mDealerScore = 0;
    mPlayerAces = 0;
    mDealerAces = 0;
    mRoundOver = false;
    mDealerDrawing = false;
    mBettingPhase = true;
    mResultMessage = "";
    mMoon1 = 0;
    mVenus5 = 0;
    mEarth10 = 0;
    mMars20 = 0;
    mSaturn50 = 0;
    mNeptune100 = 0;
    displayChipStacks();
    mReturnToWelcome = false;
    mGameOverDelay = false;
    mGameOverTimer = 0.f;

    setAlienHead(neutral);
}

