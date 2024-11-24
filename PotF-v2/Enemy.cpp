#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const sf::Vector2f& position, float speed)
    : mSpeed(speed), mAttackCooldown(2.f), mElapsedTimeSinceLastAttack(0.f), mDamageIndicatorTime(0.f), mHealth(100.f) { // Initialize mHealth
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

    // update damage indicator
    if (mDamageIndicatorTime > 0.f) {
        mDamageIndicatorTime -= deltaTime;
        if (mDamageIndicatorTime <= 0.f) {
            mShape.setFillColor(sf::Color::Green); // reset color to green
        }
    }
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(mShape);

    // render health bar above the enemy
    sf::RectangleShape healthBar;
    healthBar.setSize(sf::Vector2f(32.f * (mHealth / 100.f), 5.f)); // health bar width is proportional to health
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(mShape.getPosition().x, mShape.getPosition().y - 10.f); // position above the enemy
    window.draw(healthBar);
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

void Enemy::takeDamage(float damage) {
    mHealth -= damage; // reduce health by damage amount
    if (mHealth > 0) { mShape.setFillColor(sf::Color::Red);mDamageIndicatorTime = 0.5f; }
}

float Enemy::getHealth() const {
    return mHealth;
}