#include "Game.h"

Game::Game() : mWindow(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen), mShape(24.f)
{mShape.setFillColor(sf::Color::Green);}

void Game::run() { while (mWindow.isOpen()) { processEvents(); update(); render(); } }

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::update() {
    // Update logic here
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mShape);
    mWindow.display();
}