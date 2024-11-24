#include "Game.h"
#include "Enemy.h"
#include <vector>
#include <cmath>
#include "MainMenu.h"

Game::Game() : mWindow(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen), mShape(24.f) {
    MainMenu mainMenu(mWindow);
    mainMenu.run();

    if (!mTextureIdle.loadFromFile("Player Sword Idle 48x48.png") ||
        !mTextureRun.loadFromFile("Player_Sword_Run_48x48_1.png") ||
        !mTextureJump.loadFromFile("player_jump_left_48x48-sheet_1.png") ||
        !mTextureDeath.loadFromFile("Player Death 64x64.png") ||
        !mTextureAttack.loadFromFile("player sword atk 64x64.png")) {
    }

    // player's initial position to stand on the floor
    mSprite.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y - mSprite.getGlobalBounds().height - 160.f);

    mSprite.setTexture(mTextureIdle);
    mSprite.setPosition(mWindow.getSize().x / 2.f, 0.f);

    mVelocity = sf::Vector2f(0.f, 0.f);
    mGravity = 0.0005f; // adjust this value to control the falling speed
    mJumpSpeed = -0.3f; // adjust this value to control the jump speed
    mIsJumping = false;
    mJumpStamina = 100.f; // initial jump stamina
    mStaminaRecoveryRate = 0.01f; // rate at which stamina recovers
    mStaminaConsumptionRate = 20.f; // stamina consumed per jump
    mWalkSpeed = 0.085f; // walking speed
    mSprintSpeed = 0.18f; // sprinting speed

    // stamina bar
    mStaminaBar.setSize(sf::Vector2f(200.f, 15.f)); // 3/4 of the original height (20.f)
    mStaminaBar.setFillColor(sf::Color::Red);
    mStaminaBar.setPosition(10.f, 10.f);

    // health bar
    mHealthBar.setSize(sf::Vector2f(200.f, 15.f));
    mHealthBar.setFillColor(sf::Color::Green);
    mHealthBar.setPosition(mSprite.getPosition().x, mSprite.getPosition().y - 20.f);

    // initialize animation frames
    mCurrentFrame = 0;
    mFrameTime = 0.1f; // time per frame
    mElapsedTime = 0.f;
    mClock.restart(); // initialize the clock

    // player health
    mPlayerHealth = 100;
    mIsAttacking = false;
    mIsDead = false;
}

void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
    bool isSprinting = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mJumpStamina > 0;
    float currentSpeed = isSprinting ? mSprintSpeed : mWalkSpeed;

    if (isSprinting) {
        mJumpStamina -= mStaminaConsumptionRate * 0.001f; // consume stamina while sprinting
        if (mJumpStamina < 0) mJumpStamina = 0; // prevent stamina from going negative
    }

    if (mJumpStamina == 0) {
        currentSpeed = mWalkSpeed; // force player to walk when stamina is zero
    }

    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mVelocity.x = -currentSpeed; // adjust this value to control the left movement speed
        if (!mIsJumping) {
            mSprite.setTexture(mTextureRun);
        }
        mSprite.setScale(-1.f, 1.f); // flip the sprite horizontally
        mSprite.setOrigin(mSprite.getGlobalBounds().width, 0); // adjust the origin to the right side
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mVelocity.x = currentSpeed; // adjust this value to control the right movement speed
        if (!mIsJumping) {
            mSprite.setTexture(mTextureRun);
        }
        mSprite.setScale(1.f, 1.f); // reset the sprite to normal
        mSprite.setOrigin(0, 0); // reset the origin to the left side
        isMoving = true;
    }
    else {
        mVelocity.x = 0.f; // stop moving
    }

    if (!isMoving && !mIsJumping) {
        mSprite.setTexture(mTextureIdle);
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !mIsJumping && mJumpStamina >= mStaminaConsumptionRate) {
        mVelocity.y = mJumpSpeed;
        mIsJumping = true;
        mJumpStamina -= mStaminaConsumptionRate; // consume stamina when jumping
        mSprite.setTexture(mTextureJump);
    }

    // player attack
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        mIsAttacking = true;
        mCurrentFrame = 0;
        mSprite.setTexture(mTextureAttack);
    }
}

void Game::update() {
    mVelocity.y += mGravity;
    mSprite.move(mVelocity);

    // the floor Y position
    float floorY = mWindow.getSize().y - 160.f; // offset used for the tile map

    // prevent the player from falling through the floor
    if (mSprite.getPosition().y + mSprite.getGlobalBounds().height > floorY) {
        mSprite.setPosition(mSprite.getPosition().x, floorY - mSprite.getGlobalBounds().height);
        mVelocity.y = 0;
        mIsJumping = false;
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            mSprite.setTexture(mTextureIdle);
        }
    }

    if (mJumpStamina < 100.f) {
        mJumpStamina += mStaminaRecoveryRate;
    }

    mStaminaBar.setSize(sf::Vector2f(200.f * (mJumpStamina / 100.f), 15.f));

    // update animation frame
    mElapsedTime += mClock.restart().asSeconds();
    if (mElapsedTime >= mFrameTime) {
        mElapsedTime = 0.f;
        mCurrentFrame++;
        if (mIsAttacking) {
            if (mCurrentFrame >= 6) {
                mIsAttacking = false;
                mSprite.setTexture(mTextureIdle);
            }
            else {
                mSprite.setTextureRect(sf::IntRect(mCurrentFrame * 64, 0, 64, 64));
            }
        }
        else if (mIsDead) {
            if (mCurrentFrame >= 10) {
                mIsDead = false;
                respawnPlayer();
            }
            else {
                mSprite.setTextureRect(sf::IntRect(mCurrentFrame * 64, 0, 64, 64));
            }
        }
        else {
            if (mSprite.getTexture() == &mTextureIdle) {
                mCurrentFrame %= 10; // 10 frames for idle
            }
            else if (mSprite.getTexture() == &mTextureRun) {
                mCurrentFrame %= 8; // 8 frames for run
            }
            else if (mSprite.getTexture() == &mTextureJump) {
                mCurrentFrame %= 6; // 6 frames for jump
            }
            mSprite.setTextureRect(sf::IntRect(mCurrentFrame * 48, 0, 48, 48));
        }
    }

    // health bar position
    mHealthBar.setPosition(mSprite.getPosition().x, mSprite.getPosition().y - 20.f);
    mHealthBar.setSize(sf::Vector2f(200.f * (mPlayerHealth / 100.f), 15.f));

    // spawn enemies
    if (mEnemies.size() < 10) {
        float spawnX = static_cast<float>(rand() % mWindow.getSize().x);
        float spawnY = static_cast<float>(rand() % 2 == 0 ? -32.f : mWindow.getSize().y + 32.f); // Spawn above or below the window
        mEnemies.emplace_back(sf::Vector2f(spawnX, spawnY), mWalkSpeed); // Use player's walking speed
    }

    // update enemies
    for (auto& enemy : mEnemies) {
        enemy.setPlayerPosition(mSprite.getPosition());
        enemy.update(mElapsedTime);
        if (enemy.getBounds().intersects(mSprite.getGlobalBounds())) {
            mPlayerHealth -= 10;
            if (mPlayerHealth <= 0 && !mIsDead) {
                mIsDead = true;
                mCurrentFrame = 0;
                mSprite.setTexture(mTextureDeath);
            }
        }
    }
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.draw(mStaminaBar);
    mWindow.draw(mHealthBar);

    // render enemies
    for (auto& enemy : mEnemies) {
        enemy.render(mWindow);
    }

    mWindow.display();
}

void Game::respawnPlayer() {
    mPlayerHealth = 100;
    mSprite.setPosition(mWindow.getSize().x / 2.f, 0.f);
    mVelocity = sf::Vector2f(0.f, 0.f);
    mIsJumping = false;
    mSprite.setTexture(mTextureIdle);
}