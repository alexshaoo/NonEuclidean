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
    double offset;
    switch (direction) {
        case Direction::UP:
            offset = 0.0;
            break;
        case Direction::LEFT:
            offset = M_PI / 2.0;
			break;
        case Direction::DOWN:
			offset = M_PI;
            break;
		case Direction::RIGHT:
            offset = -M_PI / 2.0;
            break;
    }
    std::complex<double> newPosition = this->position.offset + std::polar(distance, this->position.angle + offset);

    // TODO: wall hitbox mechanic
    Node* neighbour = nullptr;
    if (newPosition.real() < 0.0) {
        neighbour = this->position.node->getNeighbour(Direction::LEFT);
        newPosition.real(fmod(newPosition.real()+1.0, 1.0));
        newPosition.imag(this->position.offset.imag());
    }
    else if (newPosition.real() > 1.0) {
        neighbour = this->position.node->getNeighbour(Direction::RIGHT);
        newPosition.real(fmod(newPosition.real()+1.0, 1.0));
        newPosition.imag(this->position.offset.imag());
    }
    else if (newPosition.imag() < 0.0) {
		neighbour = this->position.node->getNeighbour(Direction::DOWN);
		newPosition.real(this->position.offset.real());
		newPosition.imag(fmod(newPosition.imag()+1.0, 1.0));
    }
    else if (newPosition.imag() > 1.0) {
		neighbour = this->position.node->getNeighbour(Direction::UP);
		newPosition.real(this->position.offset.real());
		newPosition.imag(fmod(newPosition.imag()+1.0, 1.0));
    }
    else {
        this->position.offset = newPosition;
    }

    if (neighbour != nullptr && !neighbour->isWall()) {
		this->position.node = neighbour;
		this->position.offset = newPosition;
	}
}
