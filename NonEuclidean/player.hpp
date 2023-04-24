#pragma once

#include "main.hpp"

struct Position
{
	int x;
	int y;
};

class Player {
private:
	Position position;
public:
	Player(Position position);
	void setPosition(Position new_position);
	Position getPosition();
	~Player();
};
