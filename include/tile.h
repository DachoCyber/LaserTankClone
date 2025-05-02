#pragma once

#include <SFML/Graphics.hpp>
#include <string>


extern sf::Texture walkableTexture;
extern sf::Texture destructibleTexture;


enum TileType {
    WALKABLE_GROUND,
    DESTRUCTIBLE_BLOCK
};

class Tile {

private:

const int tileSize = 32;
public:

    
    TileType tile;
    virtual void interactWithPlayer() = 0;
    virtual void interactWithBullet() = 0;
    Tile();
};