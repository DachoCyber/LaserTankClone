#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class WalkableGround {
private:
    sf::Texture walkableGroundTex;
    sf::Sprite walkableGroundSprite;
public:
    WalkableGround() {
        try {

            if(!walkableGroundTex.loadFromFile("../Images/walkableGround.png")) {
               throw new std::runtime_error("Cannot open image walkableGround.png!");
            }
            walkableGroundSprite.setTexture(walkableGroundTex);
        }
        catch(std::string& what) {
            std::cerr << what << std::endl;
        }
    }
};