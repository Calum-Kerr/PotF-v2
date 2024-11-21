#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const sf::Vector2f& position, float speed)
    : mSpeed(speed) {
    mShape.setRadius(16.f); // 32x32 pixels
    mShape.setFillColor(sf::Color::Green);
    mShape.setPosition(position);
}

void Enemy::update(float deltaTime) {
    // enemy towards the player
    sf::Vector2f direction = mPlayerPosition - mShape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // the direction
    mShape.move(direction * mSpeed * deltaTime);
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(mShape);
}

sf::FloatRect Enemy::getBounds() const {
    return mShape.getGlobalBounds();
}

void Enemy::setPlayerPosition(const sf::Vector2f& position) {
    mPlayerPosition = position;
}