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

    // if (!mChipsTexture.loadFromFile("assets/game screen/chip stacks png.png"))
    // {
    //     std::cout << "Error opening alien head file\n";
    //     exit(2);
    // }

    //UFO buttons
    m1.setTexturePaths("assets/game screen/ufonormal.png","assets/game screen/ufohovered.png");
    m1.setText("");
    m1.setPosition({190, 555});
    m1.setSize({200, 200});

    m5.setTexturePaths("assets/game screen/ufonormal.png","assets/game screen/ufohovered.png");
    m5.setText("");
    m5.setPosition({366, 555});
    m5.setSize({200, 200});

    m10.setTexturePaths("assets/game screen/ufonormal.png","assets/game screen/ufohovered.png");
    m10.setText("");
    m10.setPosition({542, 555});
    m10.setSize({200, 200});

    m20.setTexturePaths("assets/game screen/ufonormal.png","assets/game screen/ufohovered.png");
    m20.setText("");
    m20.setPosition({718, 555});
    m20.setSize({200, 200});

    m50.setTexturePaths("assets/game screen/ufonormal.png","assets/game screen/ufohovered.png");
    m50.setText("");
    m50.setPosition({894, 555});
    m50.setSize({200, 200});

    m100.setTexturePaths("assets/game screen/ufonormal.png","assets/game screen/ufohovered.png");
    m100.setText("");
    m100.setPosition({1070, 555});
    m100.setSize({200, 200});
    
    // setupDeck();
    // for(int i = 0; i < 2; i++)
    // {
    //     dealPlayerHand();
    // }

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
    //mAlienHead.setPosition(590.f, 125.f);
    mAlienBaseX = 590.f;
    mAlienBaseY = 125.f;

    // scaler if needed 
    mAlienHead.setScale(0.65f, 0.65f);

    // sets starting expression
    setAlienHead(neutral);

    // code below here for setting base chip stack stuff
    
    // attaches textures to sprites
    // each chip stack sprite is changed by shifting the texture over to the next stack thus incrementing 1 chip at a time
    
    mMoon1Stack.setTexture(mMoon1Texture);
    mVenus5Stack.setTexture(mVenus5Texture);
    mEarth10Stack.setTexture(mEarth10Texture);
    mMars20Stack.setTexture(mMars20Texture);
    mSaturn50Stack.setTexture(mSaturn50Texture);
    mNeptune100Stack.setTexture(mNeptune100Texture);
    

    // gets image size
    // sf::Vector2u size = mMoon1Texture.getSize();

    // calculate tile size so we dont have to manually pinpoint each heads pixels (3x3 grid)


    
    // legacy code bellow
    mFrame.setSize(sf::Vector2f(580, 400));
    mFrame.setPosition(sf::Vector2f(30, 20));
    mFrame.setOutlineThickness(5);
    mFrame.setOutlineColor(sf::Color::Red);



    mRules.setPosition(sf::Vector2f(60, 450));
    mRules.setSize(sf::Vector2f(60, 20));
    mRules.setText("Rules");
    mRules.setColorTextNormal(sf::Color::Blue);
    
    mRestart.setPosition(sf::Vector2f(220, 450));
    mRestart.setSize(sf::Vector2f(60, 20));
    mRestart.setText("Restart");
    mRestart.setColorTextNormal(sf::Color::Blue);

    mResults.setPosition(sf::Vector2f(420, 450));
    mResults.setSize(sf::Vector2f(60, 20));
    mResults.setText("Results");
    mResults.setColorTextNormal(sf::Color::Blue);
    
    mExit.setText("Exit");
    mExit.setPosition({580, 450});
    mExit.setSize({60, 20});
    mExit.setColorTextNormal(sf::Color::Blue);
}

State Play::handleInput(sf::Event& e,  sf::RenderWindow& window)
{
    m1.handleInput(e, window);
    m5.handleInput(e, window);
    m10.handleInput(e, window);
    m20.handleInput(e, window);
    m50.handleInput(e, window);
    m100.handleInput(e, window);
    if (mRules.handleInput(e, window)){
        return welcome;
    }
    if (mRestart.handleInput(e, window)){
        return game;
    }
    if (mResults.handleInput(e, window)){
        return results;
    }
    if (mExit.handleInput(e, window)){
        return quit;
    }  
    return game;
}
void Play::update(double elapsedTime, sf::RenderWindow& window)
{
    m1.update();
    m5.update();
    m10.update();
    m20.update();
    m50.update();
    m100.update();
    mRules.update();
    mRestart.update();
    mResults.update();
    mExit.update();
}
void Play::render(sf::RenderWindow& window)
{
    // new code for galactic
    window.draw(mBackDrop);
    window.draw(m1);
    window.draw(m5);
    window.draw(m10);
    window.draw(m20);
    window.draw(m50);
    window.draw(m100);
    window.draw(mAlienHead);
    // window.draw(mCardOne);

    // legacy code 
    // window.draw(mFrame);
    // window.draw(mRules);
    // window.draw(mRestart);
    // window.draw(mResults);
    // window.draw(mExit);
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
            mAlienHead.setTextureRect(sf::IntRect(2*w, 0, w, h));
            mAlienHead.setPosition(x + 86.f , y - 17.f);
            break;

        case neutral:
            mAlienHead.setTextureRect(sf::IntRect(0, h, w, h));
            mAlienHead.setPosition(x, y);
            break;

        case laugh:
            mAlienHead.setTextureRect(sf::IntRect(w, h, w, h));
            mAlienHead.setPosition(x + 45.f , y );
            break;

        case blush:
            mAlienHead.setTextureRect(sf::IntRect(2*w, h, w, h));
            mAlienHead.setPosition(x + 85.f, y - 3.f );
            break;

        case jackpot:
            mAlienHead.setTextureRect(sf::IntRect(0, 2*h, w, h));
            mAlienHead.setPosition(x, y + 12.f);
            break;

        case tearsJoy:
            mAlienHead.setTextureRect(sf::IntRect(w, 2*h, w, h));
            mAlienHead.setPosition(x + 42.f, y + 10.f );
            break;

        case tearsSad:
            mAlienHead.setTextureRect(sf::IntRect(2*w, 2*h, w, h));
            mAlienHead.setPosition(x + 83.f, y + 10.f);
            break;
    }
}

void Play::setChipStacks(int clickedChip)
{
    int w = mTileWidth;
    int h = mTileHeight;

    float x = mAlienBaseX;
    float y = mAlienBaseY;

    if(clickedChip == 1)
    {
        mMoon1++;
        displayChipStacks();
    }
    if(clickedChip == 5)
    {
        mVenus5++;
        displayChipStacks();
    }
    if(clickedChip == 10)
    {
        mEarth10++;
        displayChipStacks();
    }
    if(clickedChip == 20)
    {
        mMars20++;
        displayChipStacks();
    }
    if(clickedChip == 50)
    {
        mSaturn50++;
        displayChipStacks();
    }
    if(clickedChip == 100)
    {
        mNeptune100++;
        displayChipStacks();
    }
}
void Play::displayChipStacks()
{
    // mAlienHead.setTextureRect(sf::IntRect(0, h, w, h));
    // mAlienHead.setPosition(x, y);
    // break;

    // mMoon1Stack.setTextureRect(sf::);
    // mMoon1Stack.setPosition(x,y);


    sf::Texture mMoon1Texture;
    sf::Sprite mMoon1Stack;

    sf::Texture mVenus5Texture;
    sf::Sprite mVenus5Stack;

    sf::Texture mEarth10Texture;
    sf::Sprite mEarth10Stack;

    sf::Texture mMars20Texture;
    sf::Sprite mMars20Stack;

    sf::Texture mSaturn50Texture;
    sf::Sprite mMSaturn50Stack;

    sf::Texture mNeptune100Texture;
    sf::Sprite mNeptune100Stack;
}

void Play::setupDeck()
{
    unsigned deckShuffle = std::chrono::system_clock::now().time_since_epoch().count();
                            // Pretty much this will randomize the deck using
                            // the time in miliseconds as a seed
                            // mainly used this to be able to keep the shuffle
                            // the exact same for both so a 2 card doesn't end up with 11

    vector<int> cardValue = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
                             2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
                             2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                             2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
                            // First line is first suite, second is second suite, so on so forth
    
    loadcardSprites();

    shuffle(cardValue.begin(), cardValue.end(), std::default_random_engine(deckShuffle));
    shuffle(cardSprites.begin(), cardSprites.end(), std::default_random_engine(deckShuffle));
}

void Play::setupDealerDeck()
{
     unsigned deckShuffle = std::chrono::system_clock::now().time_since_epoch().count();
                            // Pretty much this will randomize the deck using
                            // the time in miliseconds as a seed
                            // mainly used this to be able to keep the shuffle
                            // the exact same for both so a 2 card doesn't end up with 11

    vector<int> cardDealerValue = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
                                   2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
                                   2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                                   2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
                            // First line is first suite, second is second suite, so on so forth
    
    loadcardSprites();

    shuffle(cardValue.begin(), cardValue.end(), std::default_random_engine(deckShuffle + 1));
    shuffle(cardSprites.begin(), cardSprites.end(), std::default_random_engine(deckShuffle + 1));
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
    for(int j = 0; j < 13; j++) // clubs being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (16), (40), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }
        
    xDiff = 0;

    for(int j = 0; j < 13; j++) // hearts being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (68), (40), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }
    
    xDiff = 0;

    for(int j = 0; j < 13; j++) // spades being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (121), (40), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }
    
    xDiff = 0;

    for(int j = 0; j < 13; j++) // diamonds being loaded
    {
        sf::Sprite cardSprite;
        sf::Sprite cardDealerSprite;
        cardSprite.setTexture(cardSpriteSheet);
        cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (173), (43), (50)));
        cardSprite.setOrigin((5.f), (8.f));
        cardSprites.push_back(cardSprite);
        cardDealerSprites.push_back(cardDealerSprite);
        xDiff = xDiff + 41;
    }

}

void Play::dealPlayerHand()
{
    mCardOne = cardSprites.back();
    cardSprites.pop_back();
    // mCardOne.setPosition({1070 + xDiff, 555});
}

void Play::dealDealerHand()
{
    mDealerCardOne = cardDealerSprites.back();
    cardDealerSprites.pop_back();
}

/**
 * @brief orignal function for setting alien emote based on different conditions pre offset
 * 
 * @param state 
 */
// void Play::setAlienHead(alienheadstate state)
// {
//     int w = mTileWidth;
//     int h = mTileHeight;

//     switch (state)
//     {
//         case happy:
//             mAlienHead.setTextureRect(sf::IntRect(0, 0, w, h));
//             break;

//         case smug:
//             mAlienHead.setTextureRect(sf::IntRect(w, 0, w, h));
//             break;

//         case angry:
//             mAlienHead.setTextureRect(sf::IntRect(2*w, 0, w, h));
//             break;

//         case neutral:
//             mAlienHead.setTextureRect(sf::IntRect(0, h, w, h));
//             break;

//         case laugh:
//             mAlienHead.setTextureRect(sf::IntRect(w, h, w, h));
//             break;

//         case blush:
//             mAlienHead.setTextureRect(sf::IntRect(2*w, h, w, h));
//             break;

//         case jackpot:
//             mAlienHead.setTextureRect(sf::IntRect(0, 2*h, w, h));
//             break;

//         case tearsJoy:
//             mAlienHead.setTextureRect(sf::IntRect(w, 2*h, w, h));
//             break;

//         case tearsSad:
//             mAlienHead.setTextureRect(sf::IntRect(2*w, 2*h, w, h));
//             break;
//     }
//}