#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const sf::Vector2f& position, float speed)
    : mSpeed(speed), mAttackCooldown(2.f), mElapsedTimeSinceLastAttack(0.f) {
    mShape.setRadius(16.f); // 32x32 pixels
    mShape.setFillColor(sf::Color::Green);
    mShape.setPosition(position);
}

void Enemy::update(float deltaTime) {
    // move enemy towards the player
    sf::Vector2f direction = mPlayerPosition - mShape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // the direction
    mShape.move(direction * mSpeed * deltaTime);

    // update attack timer
    mElapsedTimeSinceLastAttack += deltaTime;
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

bool Enemy::canAttack() const {
    return mElapsedTimeSinceLastAttack >= mAttackCooldown;
}

void Enemy::resetAttackTimer() {
    mElapsedTimeSinceLastAttack = 0.f;
}