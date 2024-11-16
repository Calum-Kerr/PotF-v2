#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update();
    void render();
    sf::RenderWindow mWindow;
    sf::CircleShape mShape;
};

#endif // GAME_H