#include "Game.h"

Game::Game() : mWindow(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen), mShape(24.f) {
    mShape.setFillColor(sf::Color::Green);
    mShape.setPosition(mWindow.getSize().x / 2.f, 0.f);
    mVelocity = sf::Vector2f(0.f, 0.f);
    mGravity = 0.001f; // adjust this value to control the falling speed
}

void Game::run() { while (mWindow.isOpen()) { processEvents(); update(); render(); } }

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::update() {
    mVelocity.y += mGravity;
    mShape.move(mVelocity);
    // prevent the ball from falling through the bottom of the window
    if (mShape.getPosition().y + mShape.getRadius() * 2 > mWindow.getSize().y) {
        mShape.setPosition(mShape.getPosition().x, mWindow.getSize().y - mShape.getRadius() * 2);
        mVelocity.y = 0;
    }
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mShape);
    mWindow.display();
}