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

    // chip stack function is written in a way where tiles are only intentionally defined if the chip counter is > 0 
    // these if statments prevent the program from setting the individual chip objects with the entire chip stack png
    if(mMoon1 != 0)
    window.draw(mMoon1Stack);

    if(mVenus5 != 0)
        window.draw(mVenus5Stack);

    if(mEarth10 != 0)
        window.draw(mEarth10Stack);

    if(mMars20 != 0)
        window.draw(mMars20Stack);

    if(mSaturn50 != 0)
        window.draw(mSaturn50Stack);

    if(mNeptune100 != 0)
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
/**
 * @brief increments chip counter and calls displaychipStacks based on clickedChip which should be an int passed to this function when
 *        a chip denomination is clicked on the game screen
 * 
 * @param clickedChip 
 */
void Play::setChipStacks(int clickedChip)
{

    if(clickedChip == 1)
    {
        if(mMoon1 < 5)
        {
            mMoon1++;
            displayChipStacks();
        }
        else
        displayChipStacks();
        
    }
    if(clickedChip == 5)
    {
        if(mVenus5 < 5)
        {
           mVenus5++;
            displayChipStacks(); 
        }
        else
        displayChipStacks();
    }
    if(clickedChip == 10)
    {
        if(mEarth10 < 5)
        {
            mEarth10++;
            displayChipStacks();
        }
        else
        displayChipStacks();
    }
    if(clickedChip == 20)
    {
        if(mMars20 < 5)
        {
            mMars20++;
            displayChipStacks();
        }
        else
        displayChipStacks();
    }
    if(clickedChip == 50)
    {
        if(mSaturn50 < 5)
        {
            mSaturn50++;
            displayChipStacks();
        }
        else
        displayChipStacks();
    }
    if(clickedChip == 100)
    {
        if(mNeptune100 < 5)
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

    int cellW = size.x / 5;   // distance from one stack column to the next
    int cellH = size.y / 6;   // distance from one chip type row to the next

    int cropW = 80;           // actual chip stack image width
    int cropH = 80;           // actual chip stack image height

    float x = mChipsBaseX;
    float y = mChipsBaseY;

    if(mMoon1 != 0)
    {
        mMoon1 = 1;
        mMoon1Stack.setTextureRect(sf::IntRect((mMoon1 - 1) * cellW + 5, 0 * cellH, cropW, cropH));

        mMoon1Stack.setPosition(x + mMoon1OffsetX, y + mMoon1OffsetY);
    }

    if(mVenus5 != 0)
    {
        if(mVenus5 == 5)
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

    if(mEarth10 != 0)
    {
        if(mEarth10 == 5)
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

    if(mMars20 != 0)
    {
        mMars20Stack.setTextureRect(sf::IntRect((mMars20 - 1) * cellW, 3 * cellH - 10, cropW + 5, cropH));
        mMars20Stack.setPosition(x + mMars20OffsetX, y + mMars20OffsetY);
    }

    if(mSaturn50 != 0)
    {

        if(mSaturn50 == 5)
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

    if(mNeptune100 != 0)
    {

        if(mNeptune100 == 5)
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

