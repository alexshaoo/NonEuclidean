#include "main.hpp"
#include "render.hpp"
#include "node.hpp"
#include "player.hpp"

// Helper function to build world from level data
std::vector<std::vector<Node*>> buildWorld(const std::vector<std::string>& level) {
    std::vector<std::vector<Node*>> world(MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        world[i].resize(MAP_WIDTH, nullptr);
    }

    // Create nodes based on level layout
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

    // Connect neighbors (standard euclidean connections)
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            if (level[h][w] == '.' || level[h][w] == 'x') {
                if (h > 0 && (level[h - 1][w] == '.' || level[h - 1][w] == 'x'))
                    world[h][w]->addNeighbour(Direction::UP, world[h - 1][w]);
                if (h < MAP_HEIGHT - 1 && (level[h + 1][w] == '.' || level[h + 1][w] == 'x'))
                    world[h][w]->addNeighbour(Direction::DOWN, world[h + 1][w]);
                if (w > 0 && (level[h][w - 1] == '.' || level[h][w - 1] == 'x'))
                    world[h][w]->addNeighbour(Direction::LEFT, world[h][w - 1]);
                if (w < MAP_WIDTH - 1 && (level[h][w + 1] == '.' || level[h][w + 1] == 'x'))
                    world[h][w]->addNeighbour(Direction::RIGHT, world[h][w + 1]);
            }
        }
    }

    return world;
}

// Helper to cleanup world memory
void cleanupWorld(std::vector<std::vector<Node*>>& world) {
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            delete world[h][w];
        }
    }
}

// Level 1: Portal Basics
std::vector<std::vector<Node*>> mapOne() {
    auto world = buildWorld(level1);

    // Vertical portal: top of red room <-> bottom of blue room
    world[5][7]->removeNeighbour(Direction::UP);
    world[5][7]->addNeighbour(Direction::UP, world[11][22]);

    world[11][22]->removeNeighbour(Direction::DOWN);
    world[11][22]->addNeighbour(Direction::DOWN, world[5][7]);

    // Horizontal portal: green room wraps
    world[12][4]->removeNeighbour(Direction::LEFT);
    world[12][4]->addNeighbour(Direction::LEFT, world[12][8]);

    world[12][8]->removeNeighbour(Direction::RIGHT);
    world[12][8]->addNeighbour(Direction::RIGHT, world[12][4]);

    return world;
}

// Level 2: The Impossible Loop
std::vector<std::vector<Node*>> mapTwo() {
    auto world = buildWorld(level2);

    // Create an impossible square loop
    // Walking clockwise around blue room teleports you to yellow room
    world[8][12]->removeNeighbour(Direction::RIGHT);
    world[8][12]->addNeighbour(Direction::RIGHT, world[8][17]);

    world[8][27]->removeNeighbour(Direction::DOWN);
    world[8][27]->addNeighbour(Direction::DOWN, world[10][27]);

    // Walking around yellow room returns you to a different location
    world[10][17]->removeNeighbour(Direction::LEFT);
    world[10][17]->addNeighbour(Direction::LEFT, world[10][3]);

    // Green room is an exit that loops back impossibly
    world[11][28]->removeNeighbour(Direction::DOWN);
    world[11][28]->addNeighbour(Direction::DOWN, world[2][15]);

    return world;
}

// Level 3: Bigger on the Inside (TARDIS)
std::vector<std::vector<Node*>> mapThree() {
    auto world = buildWorld(level3);

    // Small blue box entrance
    // Entering from any side puts you in the MASSIVE green room below
    world[5][12]->removeNeighbour(Direction::DOWN);
    world[5][12]->addNeighbour(Direction::DOWN, world[11][15]);

    world[6][11]->removeNeighbour(Direction::RIGHT);
    world[6][11]->addNeighbour(Direction::RIGHT, world[11][15]);

    world[6][13]->removeNeighbour(Direction::LEFT);
    world[6][13]->addNeighbour(Direction::LEFT, world[11][15]);

    // The yellow inner room is even BIGGER than the green room containing it
    world[13][4]->removeNeighbour(Direction::LEFT);
    world[13][4]->addNeighbour(Direction::LEFT, world[13][27]);

    world[13][27]->removeNeighbour(Direction::RIGHT);
    world[13][27]->addNeighbour(Direction::RIGHT, world[13][4]);

    return world;
}

// Level 4: The Mirror Maze
std::vector<std::vector<Node*>> mapFour() {
    auto world = buildWorld(level4);

    // Left and right sides are the SAME space (mirror effect)
    // Walking left puts you on the right
    world[7][8]->removeNeighbour(Direction::LEFT);
    world[7][8]->addNeighbour(Direction::LEFT, world[7][25]);

    world[7][25]->removeNeighbour(Direction::RIGHT);
    world[7][25]->addNeighbour(Direction::RIGHT, world[7][8]);

    world[9][9]->removeNeighbour(Direction::LEFT);
    world[9][9]->addNeighbour(Direction::LEFT, world[9][26]);

    world[9][26]->removeNeighbour(Direction::RIGHT);
    world[9][26]->addNeighbour(Direction::RIGHT, world[9][9]);

    world[11][9]->removeNeighbour(Direction::LEFT);
    world[11][9]->addNeighbour(Direction::LEFT, world[11][26]);

    world[11][26]->removeNeighbour(Direction::RIGHT);
    world[11][26]->addNeighbour(Direction::RIGHT, world[11][9]);

    return world;
}

// Level 5: The Escher Staircase (Penrose Stairs)
std::vector<std::vector<Node*>> mapFive() {
    auto world = buildWorld(level5);

    // Create impossible staircase loop
    // Going "up" in a loop returns you to start
    world[3][11]->removeNeighbour(Direction::UP);
    world[3][11]->addNeighbour(Direction::UP, world[6][3]);

    world[6][20]->removeNeighbour(Direction::RIGHT);
    world[6][20]->addNeighbour(Direction::RIGHT, world[6][27]);

    world[6][27]->removeNeighbour(Direction::RIGHT);
    world[6][27]->addNeighbour(Direction::RIGHT, world[9][27]);

    world[9][3]->removeNeighbour(Direction::LEFT);
    world[9][3]->addNeighbour(Direction::LEFT, world[3][20]);

    // Bottom room connects back impossibly
    world[13][5]->removeNeighbour(Direction::LEFT);
    world[13][5]->addNeighbour(Direction::LEFT, world[13][27]);

    return world;
}

// Level 6: Recursive Rooms
std::vector<std::vector<Node*>> mapSix() {
    auto world = buildWorld(level6);

    // Multiple entrances to "different" blue rooms are actually the SAME room
    world[2][5]->removeNeighbour(Direction::DOWN);
    world[2][5]->addNeighbour(Direction::DOWN, world[7][15]);

    world[2][16]->removeNeighbour(Direction::DOWN);
    world[2][16]->addNeighbour(Direction::DOWN, world[7][15]);

    // The room contains itself recursively
    world[5][6]->removeNeighbour(Direction::LEFT);
    world[5][6]->addNeighbour(Direction::LEFT, world[5][17]);

    world[4][17]->removeNeighbour(Direction::UP);
    world[4][17]->addNeighbour(Direction::UP, world[2][5]);

    // Green room wraps in on itself
    world[12][6]->removeNeighbour(Direction::LEFT);
    world[12][6]->addNeighbour(Direction::LEFT, world[12][28]);

    world[12][28]->removeNeighbour(Direction::RIGHT);
    world[12][28]->addNeighbour(Direction::RIGHT, world[12][6]);

    return world;
}

// Load level based on number
std::vector<std::vector<Node*>> loadLevel(int levelNum) {
    switch (levelNum) {
        case 1: return mapOne();
        case 2: return mapTwo();
        case 3: return mapThree();
        case 4: return mapFour();
        case 5: return mapFive();
        case 6: return mapSix();
        default: return mapOne();
    }
}

// Get level name
std::string getLevelName(int levelNum) {
    switch (levelNum) {
        case 1: return "Level 1: Portal Basics";
        case 2: return "Level 2: The Impossible Loop";
        case 3: return "Level 3: Bigger on the Inside";
        case 4: return "Level 4: The Mirror Maze";
        case 5: return "Level 5: The Escher Staircase";
        case 6: return "Level 6: Recursive Rooms";
        default: return "Level 1: Portal Basics";
    }
}

Player* loadPlayer(int levelNum) {
    std::vector<std::vector<Node*>> world = loadLevel(levelNum);

    // Default spawn position
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

    int currentLevel = 1;
    Player* player = loadPlayer(currentLevel);

    sf::RenderWindow window(sf::VideoMode(X_DIM * scale, Y_DIM * scale), "Non-Euclidean Game Engine");
    window.setVerticalSyncEnabled(true);

    sf::Vector2i oldMousePosition = sf::Mouse::getPosition(window);

    sf::Font font;
    if (!font.loadFromFile("./ubuntu.ttf")) {
        std::cerr << "Failed to load font, check your system directory!" << std::endl;
        return EXIT_FAILURE;
    }

    bool inGame = true;

    // Level indicator text
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::White);
    levelText.setStyle(sf::Text::Bold);
    levelText.setPosition(10, 10);

    // Instructions text
    sf::Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setString("Press 1-6 to change levels | ESC for menu");
    instructionsText.setCharacterSize(14);
    instructionsText.setFillColor(sf::Color(255, 255, 255, 180));
    instructionsText.setPosition(10, Y_DIM * scale - 25);

    auto updateLevelText = [&]() {
        levelText.setString(getLevelName(currentLevel));
    };
    updateLevelText();

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
                case sf::Keyboard::Num1:
                case sf::Keyboard::Numpad1:
                    if (currentLevel != 1) {
                        delete player;
                        currentLevel = 1;
                        player = loadPlayer(currentLevel);
                        updateLevelText();
                    }
                    break;
                case sf::Keyboard::Num2:
                case sf::Keyboard::Numpad2:
                    if (currentLevel != 2) {
                        delete player;
                        currentLevel = 2;
                        player = loadPlayer(currentLevel);
                        updateLevelText();
                    }
                    break;
                case sf::Keyboard::Num3:
                case sf::Keyboard::Numpad3:
                    if (currentLevel != 3) {
                        delete player;
                        currentLevel = 3;
                        player = loadPlayer(currentLevel);
                        updateLevelText();
                    }
                    break;
                case sf::Keyboard::Num4:
                case sf::Keyboard::Numpad4:
                    if (currentLevel != 4) {
                        delete player;
                        currentLevel = 4;
                        player = loadPlayer(currentLevel);
                        updateLevelText();
                    }
                    break;
                case sf::Keyboard::Num5:
                case sf::Keyboard::Numpad5:
                    if (currentLevel != 5) {
                        delete player;
                        currentLevel = 5;
                        player = loadPlayer(currentLevel);
                        updateLevelText();
                    }
                    break;
                case sf::Keyboard::Num6:
                case sf::Keyboard::Numpad6:
                    if (currentLevel != 6) {
                        delete player;
                        currentLevel = 6;
                        player = loadPlayer(currentLevel);
                        updateLevelText();
                    }
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
            window.draw(levelText);
            window.draw(instructionsText);
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

    delete player;
    return 0;
}