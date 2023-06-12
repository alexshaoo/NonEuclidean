// NonEuclidean.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once
#include "main.hpp"
#include "render.hpp"
#include "node.hpp"
#include "SFML/Graphics.hpp"

Player* loadMap() {
    std::vector<std::vector<Node*>> world(16);
    for (int i = 0; i <= 15; ++i) {
        world[i].resize(30, nullptr);
    }

    for (int h = 0; h <= 15; h++) {
        for (int w = 0; w <= 29; w++) {
            switch (level[h][w]) {
            case '.':
            case 'x':
                world[h][w] = new Floor;
                break;
            case 'R':
                world[h][w] = new RedWall;
                break;
            case 'B':
                world[h][w] = new BlueWall;
                break;
            case 'G':
                world[h][w] = new GreenWall;
                break;
            case 'Y':
                world[h][w] = new YellowWall;
                break;
            }
        }
    }

    for (int h = 0; h <= 15; h++) {
        for (int w = 0; w <= 29; w++) {
            if (level[h][w] == '.') {
                if (h > 0 && level[h - 1][w] != 'x') world[h][w]->addNeighbour(Direction::UP, world[h - 1][w]);
                if (h < 15 && level[h + 1][w] != 'x') world[h][w]->addNeighbour(Direction::DOWN, world[h + 1][w]);
                if (w > 0 && level[h][w - 1] != 'x') world[h][w]->addNeighbour(Direction::LEFT, world[h][w - 1]);
                if (w < 29 && level[h][w + 1] != 'x') world[h][w]->addNeighbour(Direction::RIGHT, world[h][w + 1]);
            }
        }
    }

    world[5][7]->removeNeighbour(Direction::UP);
    world[5][7]->addNeighbour(Direction::UP, world[11][22]);

    world[11][22]->removeNeighbour(Direction::DOWN);
    world[11][22]->addNeighbour(Direction::DOWN, world[5][7]);

    world[12][4]->removeNeighbour(Direction::LEFT);
    world[12][4]->addNeighbour(Direction::LEFT, world[12][8]);

    world[12][8]->removeNeighbour(Direction::RIGHT);
    world[12][8]->addNeighbour(Direction::RIGHT, world[12][4]);

    Position pos;
    pos.node = world[8][4];
    pos.offset = std::complex<double>(0.5, 0.5);
    pos.angle = 0.9;
    Player* player = new Player(pos);

    return player;
}

int main() {
    sf::Image image;
    image.create(x_dim, y_dim);
    Player* player = loadMap();

    sf::RenderWindow window(sf::VideoMode(x_dim * scale, y_dim * scale), "Non-Euclidean Game Engine");
    sf::Event e;
    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        render(image, player);
        window.display();
    }

    return 0;
}
