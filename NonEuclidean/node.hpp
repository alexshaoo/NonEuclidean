#pragma once

#include "main.hpp"
#include "texture.hpp"

enum class Direction {
	UP = 0,
	LEFT = 1,
	DOWN = 2,
	RIGHT = 3,
};

class Node {
private:
	bool wall;
	Texture* texture;
	Node* neighbours[4];
public:
	Node(bool wall, Texture* texture=nullptr);
	virtual ~Node()=0;
	void addNeighbour(Direction direction, Node* neighbour);
	void removeNeighbour(Direction direction);
	Node* getNeighbour(Direction direction);
	bool isWall();
	Texture* getTexture();
	std::pair<Node*, double> castRay(std::complex<double> start, double angle, double distanceSoFar, double* xOffset);
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
