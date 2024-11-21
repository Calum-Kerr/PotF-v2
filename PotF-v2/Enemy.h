#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position, float speed);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    void setPlayerPosition(const sf::Vector2f& position);

private:
    sf::CircleShape mShape;
    float mSpeed;
    sf::Vector2f mPlayerPosition;
};

#endif // ENEMY_H