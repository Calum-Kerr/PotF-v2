#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>

class MainMenu { public: MainMenu(sf::RenderWindow& window); void run();
private: void processEvents();
    void render();
    sf::RenderWindow& mWindow;
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mPlayButton;
    bool mIsPlaySelected;};
#endif // MAINMENU_H