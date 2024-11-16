#include "Game.h"

Game::Game() : mWindow(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen), mShape(24.f) {
    mShape.setFillColor(sf::Color::Green);
    mShape.setPosition(mWindow.getSize().x / 2.f, 0.f);
    mVelocity = sf::Vector2f(0.f, 0.f);
    mGravity = 0.001f; // adjust this value to control the falling speed
    mJumpSpeed = -0.3f; // adjust this value to control the jump speed
    mIsJumping = false;
    mJumpStamina = 100.f; // initial jump stamina
    mStaminaRecoveryRate = 0.01f; // rate at which stamina recovers
    mStaminaConsumptionRate = 20.f; // stamina consumed per jump
}

void Game::run() { while (mWindow.isOpen()) { processEvents(); update(); render(); } }

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mVelocity.x = -0.1f; // adjust this value to control the left movement speed
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mVelocity.x = 0.1f; // adjust this value to control the right movement speed
    } else {
        mVelocity.x = 0.f;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !mIsJumping && mJumpStamina >= mStaminaConsumptionRate) {
        mVelocity.y = mJumpSpeed;
        mIsJumping = true;
        mJumpStamina -= mStaminaConsumptionRate;
    }
}

void Game::update() {
    mVelocity.y += mGravity;
    mShape.move(mVelocity);
    // prevent the ball from falling through the bottom of the window
    if (mShape.getPosition().y + mShape.getRadius() * 2 > mWindow.getSize().y) {
        mShape.setPosition(mShape.getPosition().x, mWindow.getSize().y - mShape.getRadius() * 2);
        mVelocity.y = 0;
        mIsJumping = false;
    }
    // recover jump stamina over time
    if (mJumpStamina < 100.f) {
        mJumpStamina += mStaminaRecoveryRate;
    }
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mShape);
    mWindow.display();
}