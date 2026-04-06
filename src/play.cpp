#include "../header/play.h"
Play::Play()
{
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
    window.draw(mFrame);
    window.draw(mRules);
    window.draw(mRestart);
    window.draw(mResults);
    window.draw(mExit);
}