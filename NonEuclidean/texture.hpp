#pragma once

#include "main.hpp"

class Texture {
private:
public:
	const int width, height;
	sf::Color** data;
	Texture(int width, int height);
	Texture(int width, int height, std::initializer_list<std::initializer_list<uint32_t>> pixels);
	~Texture();
};

extern Texture redWallTexture;
extern Texture greenWallTexture;
extern Texture blueWallTexture;
extern Texture yellowWallTexture;