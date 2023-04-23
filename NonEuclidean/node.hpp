#pragma once
class Node
{
public:
	Node(bool wall);
	bool isWall();
	virtual ~Node() = 0;
};



