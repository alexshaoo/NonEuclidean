#pragma once

#include "main.hpp"
#include "texture.hpp"

enum class Direction {
	RIGHT = 0,
	FORWARD = 1,
	LEFT = 2,
	BACK = 3
};

class Node {
private:
	bool wall;
	Node* neighbours[4];
	Texture* texture;
public:
	Node(bool wall, Texture* texture=nullptr);
	void addNeighbour(Direction direction, Node* neighbour);
	void removeNeighbour(Direction direction);
	Node* getNeighbour(Direction direction);
	bool isWall();
	std::pair<Node*, double> castRay(std::complex<double> start, double angle, double distanceSoFar, double* offset);
	virtual ~Node()=0;
};

class Floor : public Node {
private:
public:
	Floor() : Node(false, nullptr) {};
	~Floor() {};
};

class RedWall : public Node {
private:
public:
	RedWall() : Node(true, &redWallTexture) {};
	~RedWall() {};
};

class GreenWall : public Node {
private:
public:
	GreenWall() : Node(true, &greenWallTexture) {};
	~GreenWall() {};
};

class BlueWall : public Node {
private:
public:
	BlueWall() : Node(true, &blueWallTexture) {};
	~BlueWall() {};
};

class YellowWall : public Node {
private:
public:
	YellowWall() : Node(true, &yellowWallTexture) {};
	~YellowWall() {};
};
