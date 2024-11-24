#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window) : mWindow(window), mIsPlaySelected(false) {
    !mFont.loadFromFile("arial.ttf");
    mTitle.setFont(mFont);
    mTitle.setString("PotF");
    mTitle.setCharacterSize(50);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setPosition(mWindow.getSize().x / 2.f - mTitle.getGlobalBounds().width / 2.f, 100.f);
    mPlayButton.setFont(mFont);
    mPlayButton.setString("Play Game");
    mPlayButton.setCharacterSize(30);
    mPlayButton.setFillColor(sf::Color::White);
    mPlayButton.setPosition(mWindow.getSize().x / 2.f - mPlayButton.getGlobalBounds().width / 2.f, 300.f);
}

void MainMenu::run() {
    while (mWindow.isOpen() && !mIsPlaySelected) {
        processEvents();
        render();
    }
}

void MainMenu::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (mPlayButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    mIsPlaySelected = true;
                }
            }
        }
    }
}

void MainMenu::render() {
    mWindow.clear();
    mWindow.draw(mTitle);
    mWindow.draw(mPlayButton);
    mWindow.display();
}