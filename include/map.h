#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map : public sf::Drawable {
public:
    Map();
    virtual ~Map() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    bool isWalkable(int x, int y) const;
    sf::Vector2f getTilePosition(int x, int y) const;
    int getTileSize() const { return tileSize; }

private:
    void loadTextures();
    void buildMap();

    const int tileSize = 32;
    const int mapWidth = 19;
    const int mapHeight = 19;
    
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<sf::Sprite>> sprites;
    
    sf::Texture walkableTexture;
    sf::Texture destructibleTexture;
};