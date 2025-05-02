#include "include/game.h"

MainGame::MainGame(int windowSizeX, int windowSizeY) :
    window(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowSizeX, windowSizeY), 
        "Laser Tank", 
        sf::Style::Close)),
    player(3, 3, windowSizeX, windowSizeY),
    tileMap(),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY)
{
    window->setFramerateLimit(60);
}

void MainGame::run() {
    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window->close();
        }

        timeSinceLastUpdate += gameClock.restart();
        
        // Fixed timestep updates
        while(timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            handleInput();
            update();
        }

        render();
    }
}

void MainGame::handleInput() {
    if(moveQueued) return;

    sf::Vector2i newGridPos = player.getGridPosition();
    bool moved = false;

    // UP
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if(!upPressed) {
            upPressed = true;
            if(player.getDir() != UP) {
                player.setDir(UP);
            } else {
                newGridPos.y -= 1;
                moved = true;
            }
        }
    } else {
        upPressed = false;
    }

    // DOWN
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if(!downPressed) {
            downPressed = true;
            if(player.getDir() != DOWN) {
                player.setDir(DOWN);
            } else {
                newGridPos.y += 1;
                moved = true;
            }
        }
    } else {
        downPressed = false;
    }

    // LEFT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(!leftPressed) {
            leftPressed = true;
            if(player.getDir() != LEFT) {
                player.setDir(LEFT);
            } else {
                newGridPos.x -= 1;
                moved = true;
            }
        }
    } else {
        leftPressed = false;
    }

    // RIGHT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if(!rightPressed) {
            rightPressed = true;
            if(player.getDir() != RIGHT) {
                player.setDir(RIGHT);
            } else {
                newGridPos.x += 1;
                moved = true;
            }
        }
    } else {
        rightPressed = false;
    }

    if(moved && validMove(newGridPos.x, newGridPos.y)) {
        player.setGridPosition(newGridPos);
        moveQueued = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player.fireBullet();
    }
}

void MainGame::update() {
    // Reset move queue if no keys pressed
    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
        moveQueued = false;
    }

    // Update bullet if exists
    if(player.getBullet() != nullptr) {
        player.getBullet()->update(timePerFrame);
    }
}

void MainGame::render() {
    window->clear(sf::Color::White);
    window->draw(tileMap);
    window->draw(player);
    window->display();
}

bool MainGame::validMove(int x, int y) const {
    return x >= 0 && x < (windowSizeX / tileSize) && 
           y >= 0 && y < (windowSizeY / tileSize);
}