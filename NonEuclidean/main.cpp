#include "main.hpp"
#include "render.hpp"
#include "node.hpp"
#include "player.hpp"


std::vector<std::vector<Node*>> mapOne() {
    std::vector<std::vector<Node*>> world(MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        world[i].resize(MAP_WIDTH, nullptr);
    }

    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
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

    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
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

    return world;
}

Player* loadPlayer() {
    std::vector<std::vector<Node*>> world = mapOne();

    // spawn at (8,4) facing 0.9 radians
    Position pos;
    pos.node = world[8][4];
    pos.offset = std::complex<double>(0.5, 0.5);
    pos.angle = 0.9;
    Player* player = new Player(pos);

    return player;
}

int main() {
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    image.create(X_DIM, Y_DIM);
    texture.create(X_DIM, Y_DIM);
    texture.update(image);
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(scale, scale);
    Player* player = loadPlayer();
    

    sf::RenderWindow window(sf::VideoMode(X_DIM * scale, Y_DIM * scale), "Non-Euclidean Game Engine");
    window.setVerticalSyncEnabled(true);

    sf::Vector2i oldMousePosition = sf::Mouse::getPosition(window);

    sf::Font font;
    if (!font.loadFromFile("./ubuntu.ttf")) {
        std::cerr << "Failed to load font, check your system directory!" << std::endl;
        return EXIT_FAILURE;
    }

    bool inGame = true;

    sf::RectangleShape quitButton(sf::Vector2f(200, 50));
    quitButton.setFillColor(sf::Color::Red);
    quitButton.setPosition((X_DIM * scale) / 2 - quitButton.getSize().x / 2, (Y_DIM * scale) / 2 - quitButton.getSize().y / 2 - 100);

    sf::Text quitButtonText;
    quitButtonText.setFont(font);
    quitButtonText.setString("Quit");
    quitButtonText.setCharacterSize(24);
    quitButtonText.setFillColor(sf::Color::White);
    quitButtonText.setStyle(sf::Text::Bold);
    quitButtonText.setPosition(quitButton.getPosition().x + quitButton.getSize().x / 2 - quitButtonText.getLocalBounds().width / 2, quitButton.getPosition().y + quitButton.getSize().y / 2 - quitButtonText.getLocalBounds().height / 2);

    sf::RectangleShape resumeButton(sf::Vector2f(200, 50));
    resumeButton.setFillColor(sf::Color::Green);
    resumeButton.setPosition((X_DIM * scale) / 2 - resumeButton.getSize().x / 2, (Y_DIM * scale) / 2 - resumeButton.getSize().y / 2 + 100);

    sf::Text resumeButtonText;
    resumeButtonText.setFont(font);
    resumeButtonText.setString("Resume");
    resumeButtonText.setCharacterSize(24);
    resumeButtonText.setFillColor(sf::Color::White);
    resumeButtonText.setStyle(sf::Text::Bold);
    resumeButtonText.setPosition(resumeButton.getPosition().x + resumeButton.getSize().x / 2 - resumeButtonText.getLocalBounds().width / 2, resumeButton.getPosition().y + resumeButton.getSize().y / 2 - resumeButtonText.getLocalBounds().height / 2);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::KeyPressed:
                switch (e.key.code) {
                case sf::Keyboard::Escape:
                    inGame = !inGame;
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (!inGame) {
                    if (quitButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                        window.close();
                    }
                    if (resumeButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                        inGame = true;
                    }
                }
                break;
            case sf::Event::MouseMoved:
                if (inGame) {
                    // Compute the difference between the old and the new position
                    sf::Vector2i diff = sf::Mouse::getPosition(window) - oldMousePosition;

                    // Use this difference to update the player's view
                    player->rotate(-diff.x * MOUSE_SENSITIVITY);

                    // Reset mouse position
                    sf::Mouse::setPosition(oldMousePosition, window);
                }
                break;
            }
        }

        window.clear();
        if (inGame) {
            window.setMouseCursorVisible(false);
            window.setMouseCursorGrabbed(true);
            // Save the new mouse position before recentering
            sf::Vector2i newMousePosition = sf::Mouse::getPosition(window);
            double rotate = -(newMousePosition.x - oldMousePosition.x) * MOUSE_SENSITIVITY;
            player->rotate(rotate);

            // Reset mouse position to the center
            sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);

            // Now the old mouse position should be updated to the new center
            oldMousePosition = sf::Mouse::getPosition(window);

            player->rotate(rotate);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player->move(Direction::UP, PLAYER_MOVE_DISTANCE);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player->move(Direction::DOWN, PLAYER_MOVE_DISTANCE);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player->move(Direction::LEFT, PLAYER_MOVE_DISTANCE);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player->move(Direction::RIGHT, PLAYER_MOVE_DISTANCE);
            }
            render(image, player);
            texture.update(image);
            window.draw(sprite);
        } else {
            window.setMouseCursorVisible(true);
            window.setMouseCursorGrabbed(false);
            window.clear(sf::Color::White);
            window.draw(quitButton);
            window.draw(quitButtonText);
            window.draw(resumeButton);
            window.draw(resumeButtonText);
        }
        window.display();
    }

    return 0;
}