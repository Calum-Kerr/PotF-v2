#include "TileMap.h"

TileMap::TileMap() {
    // Constructor
}

bool TileMap::load(const std::string& filename) {
    if (!mTexture.loadFromFile(filename)) {return false;}
    mSprite.setTexture(mTexture);
    return true;
}

void TileMap::draw(sf::RenderWindow& window) {window.draw(mSprite);}

void TileMap::setPosition(float x, float y) { mSprite.setPosition(x, y);}