#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>

class Game { public: Game(); void run();
private: void processEvents();
    void update();
    void render();
    void respawnPlayer();

    sf::RenderWindow mWindow;
    sf::CircleShape mShape;
    sf::Texture mTextureIdle;
    sf::Texture mTextureRun;
    sf::Texture mTextureJump;
    sf::Texture mTextureDeath;
    sf::Texture mTextureAttack;
    sf::Sprite mSprite;
    sf::Vector2f mVelocity;
    float mGravity;
    float mJumpSpeed;
    bool mIsJumping;
    float mJumpStamina;
    float mStaminaRecoveryRate;
    float mStaminaConsumptionRate;
    float mWalkSpeed;
    float mSprintSpeed;
    sf::RectangleShape mStaminaBar;
    sf::RectangleShape mHealthBar;
    int mCurrentFrame;
    float mFrameTime;
    float mElapsedTime;
    sf::Clock mClock;

    int mPlayerHealth;
    bool mIsAttacking;
    bool mIsDead;
    std::vector<Enemy> mEnemies;
	float mEnemySpawnTimer;
	float mEnemySpawnTimerMax;
	float mEnemyMaxVelocity;
	float mEnemyMinVelocity;
	float mEnemyVelocity;
	float mEnemySpawnTimerIncrease;
    float mEnemyVelocityIncrease;
};
#endif // GAME_H