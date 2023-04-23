#pragma once

#include "main.hpp"
#include "node.hpp"

struct Position
{
	int x;
	int y;
};

class Player
{
private:
	Position position;
public:
	Player(Position position);
	void setPosition(Position new_position);
	Position getPosition();
	~Player();
};
