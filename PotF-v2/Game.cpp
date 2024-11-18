#include "Game.h"

Game::Game() : mWindow(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen), mShape(24.f) {
    // Load textures
    if (!mTextureIdle.loadFromFile("Player Sword Idle 48x48.png") ||
        !mTextureRun.loadFromFile("Player_Sword_Run_48x48_1.png") ||
        !mTextureJump.loadFromFile("player_jump_left_48x48-sheet_1.png")) {
        // Handle error
    }

    mSprite.setTexture(mTextureIdle);
    mSprite.setPosition(mWindow.getSize().x / 2.f, 0.f);

    mVelocity = sf::Vector2f(0.f, 0.f);
    mGravity = 0.0005f; // adjust this value to control the falling speed
    mJumpSpeed = -0.3f; // adjust this value to control the jump speed
    mIsJumping = false;
    mJumpStamina = 100.f; // initial jump stamina
    mStaminaRecoveryRate = 0.01f; // rate at which stamina recovers
    mStaminaConsumptionRate = 20.f; // stamina consumed per jump
    mWalkSpeed = 0.085f; // walking speed
    mSprintSpeed = 0.18f; // sprinting speed

    // stamina bar
    mStaminaBar.setSize(sf::Vector2f(200.f, 15.f)); // 3/4 of the original height (20.f)
    mStaminaBar.setFillColor(sf::Color::Red);
    mStaminaBar.setPosition(10.f, 10.f);

    // initialize animation frames
    mCurrentFrame = 0;
    mFrameTime = 0.1f; // time per frame
    mElapsedTime = 0.f;
    mClock.restart(); // initialize the clock
}

void Game::run() { while (mWindow.isOpen()) { processEvents(); update(); render(); } }

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
    bool isSprinting = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mJumpStamina > 0;
    float currentSpeed = isSprinting ? mSprintSpeed : mWalkSpeed;

    if (isSprinting) {
        mJumpStamina -= mStaminaConsumptionRate * 0.001f; // consume stamina while sprinting
        if (mJumpStamina < 0) mJumpStamina = 0; // prevent stamina from going negative
    }

    if (mJumpStamina == 0) {
        currentSpeed = mWalkSpeed; // force player to walk when stamina is zero
    }

    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mVelocity.x = -currentSpeed; // adjust this value to control the left movement speed
        mSprite.setTexture(mTextureRun);
        mSprite.setScale(-1.f, 1.f); // flip the sprite horizontally
        mSprite.setOrigin(mSprite.getGlobalBounds().width, 0); // adjust the origin to the right side
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mVelocity.x = currentSpeed; // adjust this value to control the right movement speed
        mSprite.setTexture(mTextureRun);
        mSprite.setScale(1.f, 1.f); // reset the sprite to normal
        mSprite.setOrigin(0, 0); // reset the origin to the left side
        isMoving = true;
    }
    else {
        mVelocity.x = 0.f; // stop moving
    }

    if (!isMoving && !mIsJumping) {
        mSprite.setTexture(mTextureIdle);
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !mIsJumping && mJumpStamina >= mStaminaConsumptionRate) {
        mVelocity.y = mJumpSpeed;
        mIsJumping = true;
        mJumpStamina -= mStaminaConsumptionRate; // consume stamina when jumping
        mSprite.setTexture(mTextureJump);
    }
}


void Game::update() {
    mVelocity.y += mGravity;
    mSprite.move(mVelocity);
    // prevent the ball from falling through the bottom of the window
    if (mSprite.getPosition().y + mSprite.getGlobalBounds().height > mWindow.getSize().y) {
        mSprite.setPosition(mSprite.getPosition().x, mWindow.getSize().y - mSprite.getGlobalBounds().height);
        mVelocity.y = 0;
        mIsJumping = false;
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            mSprite.setTexture(mTextureIdle);
        }
    }
    // recover jump stamina over time
    if (mJumpStamina < 100.f) {
        mJumpStamina += mStaminaRecoveryRate; 
    }

    // update stamina bar size
    mStaminaBar.setSize(sf::Vector2f(200.f * (mJumpStamina / 100.f), 15.f)); // 3/4 of the original height (20.f)

    // update animation frame
    mElapsedTime += mClock.restart().asSeconds();
    if (mElapsedTime >= mFrameTime) {
        mElapsedTime = 0.f;
        mCurrentFrame++;
        if (mSprite.getTexture() == &mTextureIdle) {
            mCurrentFrame %= 10; // 10 frames for idle
        } else if (mSprite.getTexture() == &mTextureRun) {
            mCurrentFrame %= 8; // 9 frames for run
        } else if (mSprite.getTexture() == &mTextureJump) {
            mCurrentFrame %= 6; // 6 frames for jump
        }
        mSprite.setTextureRect(sf::IntRect(mCurrentFrame * 48, 0, 48, 48));
    }
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.draw(mStaminaBar);
    mWindow.display();
}