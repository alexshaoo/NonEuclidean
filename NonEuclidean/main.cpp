// NonEuclidean.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once
#include "main.hpp"
#include "render.hpp"
#include "node.hpp"
#include "SFML/Graphics.hpp"

int main() {
    sf::Image image;
    image.create(x_dim, y_dim);
    Player* player = loadMap();

    sf::RenderWindow window(sf::VideoMode(x_dim*scale, y_dim*scale), "Non-Euclidean Game Engine");
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

Player* loadMap() {
    std::vector<std::vector<Node*>> map(16);
    for (int i = 0; i <= 15; ++i) {
        map[i].resize(30, nullptr);
    }

    Position pos;
    pos.node = map[8][4];
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
