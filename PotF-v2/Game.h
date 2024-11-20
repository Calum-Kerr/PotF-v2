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
    sf::Vector2f mVelocity;
    float mGravity;
    float mJumpSpeed;
    bool mIsJumping;
    float mJumpStamina;
    float mStaminaRecoveryRate;
    float mStaminaConsumptionRate;
    sf::RectangleShape mStaminaBar;
    float mWalkSpeed;
    float mSprintSpeed;
    sf::Texture mTextureIdle;
    sf::Texture mTextureRun;
    sf::Texture mTextureJump;
    sf::Sprite mSprite;
    int mCurrentFrame; // Changed from float to int
    float mFrameTime;
    float mElapsedTime;
    sf::Clock mClock;
};

#endif // GAME_H