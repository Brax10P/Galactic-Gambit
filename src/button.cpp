#include "../header/button.h"
//Default constructor that loads texture from file “button.png” and font from “college.ttf” file.
    //set texture for mButton, set the origin to the middle of the button (texture), 
    //set color to White, position to {300,100}, set state to normal, and scale to 100%
    //set font for the text, set the size of the text to the half of Button size, set the origin to the middle of the text 
    //and set position at the middle of the button, assign “Push me!” as a string of the button
Button::Button()
    : Button("Push me!", {300.f, 100.f}, {100.f, 50.f}, sf::Color::White)
{
}
    //Constructor that sets button label to s, button position to the position,  button size to size (given in pixels), and button color to color.
Button::Button(std::string s, sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
    if (!mTexture.loadFromFile("assets/normalbutton.png"))
    {
        std::cout << "Error opening normalbutton.png\n";
        exit(1);
    }

    mButton.setTexture(mTexture);
    
    //get size of image
    sf::Vector2u imageSize = mTexture.getSize();
    // //change origin to the center of the image (makes rotation easy)
    mButton.setOrigin(imageSize.x/2, imageSize.y/2);
    // //set position
    //sf::Vector2f position={300,200};
    mPosition = position;
    mButton.setPosition(mPosition.x,mPosition.y);
    //choose color
    mButtonColor = color;
    mButton.setColor(mButtonColor);
    // //set size as a ration of original size
    mButton.setScale(size.x/imageSize.x, size.y/imageSize.y);
    //Make label
    if (!mFont.loadFromFile("assets/VintageCharm-Regular.otf"))
    {
        std::cout<<"Error opening file\n";
        exit(2);
    }
    mText.setFont(mFont);
    //choose the font size based on button size (I choose half)
    unsigned int fontSize = mButton.getGlobalBounds().height/4;
    mText.setCharacterSize(fontSize);
    // //set label
    mText.setString(s);
    //set origin to the middle
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    //set position at the middle of the button
    mText.setPosition(
        mPosition.x,
        mPosition.y + mButton.getGlobalBounds().height / 2.f + 5.f
    );
    //choose colors
    mTextNormal = sf::Color::Blue;
    mTextHover = sf::Color::Red;
    mText.setFillColor(mTextNormal);
    mBtnState=normal;
}
//change button position to position (what else needs to be changed?)
void Button::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mButton.setPosition(mPosition.x,mPosition.y);

    //choose the font size based on button size (I choose half)
    //unsigned int fontSize = mButton.getGlobalBounds().height/2;
    
    //set origin to the middle
    //set position at the middle of the button
    mText.setPosition(
        mPosition.x,
        mPosition.y + mButton.getGlobalBounds().height / 2.f + 5.f
    );
}
//change button size to size (what else needs to be changed?)
void Button::setSize(sf::Vector2f size)
{
    sf::Vector2u imageSize = mTexture.getSize();

    if (imageSize.x == 0 || imageSize.y == 0)
    {
        std::cout << "Cannot resize button: texture not loaded\n";
        return;
    }

    mButton.setScale(size.x / imageSize.x, size.y / imageSize.y);

    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);

    mText.setPosition(
        mPosition.x,
        mPosition.y + mButton.getGlobalBounds().height / 2.f + 5.f
    );
}

/**
 * @brief change button color
 * 
 * @param btnColor new color
 */
void Button::setColor(sf::Color btnColor)
{
    mButtonColor = btnColor;
    mButton.setColor(mButtonColor);
}
//change button label to s (what else needs to be changed?)
void Button::setText(std::string s)
{
    mText.setString(s);
    //set origin to the middle
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    //set position at the middle of the button
    //unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setPosition(
        mPosition.x,
        mPosition.y + mButton.getGlobalBounds().height / 2.f + 5.f
    );
}

bool Button::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    //get position of the mouse
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(mPos);
    bool mouseInButton =    mousePosition.x >= mButton.getPosition().x - mButton.getGlobalBounds().width/2
                            && mousePosition.x <= mButton.getPosition().x + mButton.getGlobalBounds().width/2
                            && mousePosition.y >= mButton.getPosition().y - mButton.getGlobalBounds().height/2
                            && mousePosition.y <= mButton.getPosition().y + mButton.getGlobalBounds().height/2;
    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            mBtnState = state::hovered;
        }
        else
        {
            mBtnState = state::normal;
        }
    }
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if(e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mBtnState = state::clicked;
                return true;
            }
            else
            {
                mBtnState = state::normal;
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mBtnState = state::hovered;
            }
            else
            {
                mBtnState = state::normal;
            }
        }
    }
    return false;
    
}
void Button::update()
{
    switch (mBtnState)
    {
    case normal:
        mButton.setRotation(0);
        mText.setFillColor(mTextNormal);
        mTexture.loadFromFile(mNormalPath);
        mButton.setTexture(mTexture);
        break;

    case hovered:
        mButton.setRotation(0);
        mText.setFillColor(mTextHover);
        mTexture.loadFromFile(mHoverPath);
        mButton.setTexture(mTexture);
        break;

    case clicked:
        mText.setFillColor(mTextHover);
        mTexture.loadFromFile(mHoverPath);
        mButton.setTexture(mTexture);
        break;
    }
}
void Button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mText, states);
}

/**
 * @brief function to change text size of button
 * 
 * @param size 
 */
void Button::setTextSize (int size)
{
    mText.setCharacterSize(size);
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    //set position at the middle of the button
    //unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setPosition
    (
        mPosition.x,
        mPosition.y + mButton.getGlobalBounds().height / 2.f + 5.f
    );
}

/**
 * @brief Sets button png to normal/hovered
 * 
 * @param normalPath 
 * @param hoverPath 
 */
void Button::setTexturePaths(std::string normalPath, std::string hoverPath)
{
    mNormalPath = normalPath;
    mHoverPath = hoverPath;

    if (!mTexture.loadFromFile(mNormalPath))
    {
        std::cout << "Error opening file\n";
        exit(1);
    }

    mButton.setTexture(mTexture);

    sf::Vector2u imageSize = mTexture.getSize();
    if (imageSize.x == 0 || imageSize.y == 0)
    {
        std::cout << "Texture has invalid size\n";
        exit(1);
    }    
    mButton.setOrigin(imageSize.x / 2.f, imageSize.y / 2.f);
}