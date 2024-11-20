#pragma once
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

class TileMap {
public:
    TileMap();
    bool load(const std::string& filename);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);

private:sf::Texture mTexture; sf::Sprite mSprite;};

#endif // TILEMAP_H