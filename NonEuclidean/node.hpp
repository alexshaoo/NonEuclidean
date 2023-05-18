#pragma once

#include "main.hpp"
enum class Direction {
	RIGHT = 0,
	FORWARD = 1,
	LEFT = 2,
	BACK = 3
};

class Node
{
private:
	bool wall;
	Node* neighbours[4];
public:
	Node(bool wall);
	void addNeighbour(Direction direction);
	void removeNeighbour(Direction direction);
	Node* getNeighbour(Direction direction);
	bool isWall();
	std::pair<Node*, double> castRay(std::complex<double> start, double angle, double distanceSoFar, double* offset);
	virtual ~Node() = 0;
};


