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
        std::cout << "Error opening alien head file\n";
        exit(2);
    }

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
    sf::Vector2u size = mMoon1Texture.getSize();

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
    
    mRules.update();
    mRestart.update();
    mResults.update();
    mExit.update();
}
void Play::render(sf::RenderWindow& window)
{
    // new code for galactic
    window.draw(mBackDrop);

    
    window.draw(mAlienHead);
    
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
    mAlienHead.setTextureRect(sf::IntRect(0, h, w, h));
    mAlienHead.setPosition(x, y);
    break;

    mMoon1Stack.setTextureRect(sf::);
    mMoon1Stack.setPosition(x,y);


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