#include "include/map.h"
#include "include/tile.h"
#include "include/extractMatrix.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

Map::Map() {
    readMapFromXML(tileMap);
    
    loadTextures();
    buildMap();
}

void Map::loadTextures() {
    if (!walkableTexture.loadFromFile("Images/walkableGround.png")) {
        throw std::runtime_error("Failed to load walkable texture");
    }
    if (!destructibleTexture.loadFromFile("Images/destructibleBlock.png")) {
        throw std::runtime_error("Failed to load destructible texture");
    }
}

void Map::buildMap() {
    sprites.resize(mapHeight, std::vector<sf::Sprite>(mapWidth));
    
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            sf::Sprite sprite;
            switch(tileMap[y][x]) {
                case 1: case 2: case 5: case 6:
                    sprite.setTexture(walkableTexture);
                    break;
                case 3: case 4: case 7: case 8:
                    sprite.setTexture(destructibleTexture);
                    break;
                default:
                    break;
            }
            
            sprite.setPosition(x * tileSize, y * tileSize);
            sprites[y][x] = sprite;
        }
    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& row : sprites) {
        for (const auto& sprite : row) {
            target.draw(sprite);
        }
    }
}

bool Map::isWalkable(int x, int y) const {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return false;
    }
    int tile = tileMap[y][x];
    return (tile == 1 || tile == 2 || tile == 5 || tile == 6);
}

sf::Vector2f Map::getTilePosition(int x, int y) const {
    return sf::Vector2f(x * tileSize, y * tileSize);
}