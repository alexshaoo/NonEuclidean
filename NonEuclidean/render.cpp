#include "render.hpp"

const sf::Color ceiling_colour(0x73c1c6FF);
const sf::Color floor_colour(0xa79ab2FF);

void render(sf::Image& image, Player* player) {
	// ceiling/floor
	for (int x = 0; x < x_dim; x++) {
		for (int y = 0; y < y_dim; y++) {
			image.setPixel(x, y, ceiling_colour);
		}
		for (int y = y_dim / 2; y < y_dim; y++) {
			image.setPixel(x, y, floor_colour);
		}
	}

	Position position = player->getPosition();
}