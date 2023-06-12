#include "render.hpp"

const sf::Color ceiling_colour(0x73c1c6FF);
const sf::Color floor_colour(0xa79ab2FF);
const double FOV = 70.0 * M_PI / 180.0;
const double depth = (double)x_dim / 2.0 / tan(FOV / 2.0);

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

	Position pos = player->getPosition();

	for (int x = 0; x < x_dim; ++x) {
		double tanVal = (double)(x_dim / 2 - x) / depth;
		double rayAngleOffset = atan(tanVal);
		double rayAngle = fmod(pos.angle + rayAngleOffset + 2.0 * M_PI, 2.0 * M_PI);
		double txOffset;
		std::pair<Node*, double> ray = pos.node->castRay(pos.offset, rayAngle, 0.0, &txOffset);
		Node* wall = ray.first;
		double dist = ray.second;
	
		// TODO: do something about fish lensing

		if (wall == nullptr || wall->getTexture() == nullptr) {
			continue;
		}
		double originalWallHeight = ((double)x_dim / dist);
		int screenWallHeight = ((int)originalWallHeight > y_dim) ? y_dim : (int)originalWallHeight;
		for (int y = y_dim / 2 - screenWallHeight / 2; y < y_dim / 2 + screenWallHeight / 2; ++y) {
			double tx = txOffset;
			double ty = ((double)((double)y + 0.5 - (double)y_dim / 2) / originalWallHeight) + 0.5;
			sf::Color colour = wall->getTexture()->data[(size_t)(ty * wall->getTexture()->height)][(size_t)(tx * wall->getTexturee()->width)];
			image.setPixel(x, y, colour);
		}
	}
}