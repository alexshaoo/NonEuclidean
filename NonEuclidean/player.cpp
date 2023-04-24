#include "player.hpp"

Player::Player(Position position) {
    this->position = position;
}

void Player::setPosition(Position position)  {
    this->position = position;
}

Position Player::getPosition() {
    return this->position;
}

Player::~Player() {}