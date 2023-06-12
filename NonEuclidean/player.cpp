#include "player.hpp"

Player::Player(Position position) : position(position) {}
Player::~Player() {}

Position Player::getPosition() {
    return this->position;
}

void Player::setPosition(Position position)  {
    if (position.node == nullptr) {
        throw std::runtime_error("[" __FUNCTION__ "] New node was a nullptr.");
    }
    if (position.offset.real() < 0.0 || position.offset.real() > 1.0 || position.offset.imag() < 0.0 || position.offset.imag() > 1.0) {
        throw std::runtime_error("[" __FUNCTION__ "] Position out of bounds.");
    }
    this->position = position;
}

void Player::rotate(double offset) {
    this->position.angle += offset;
    this->position.angle = fmod(this->position.angle + 2.0 * M_PI, 2.0 * M_PI);
}

void Player::move(Direction direction, double distance) {
    ;
}
