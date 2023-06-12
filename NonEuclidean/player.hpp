#pragma once

#include "main.hpp"
#include "node.hpp"

struct Position {
	Node* node;
	std::complex<double> offset;
	double angle;
};

class Player {
private:
	Position position;
public:
	Player(Position position);
	~Player();
	Position getPosition();
	void setPosition(Position position);
	void rotate(double offset);
	void move(Direction direction, double distance);
};
