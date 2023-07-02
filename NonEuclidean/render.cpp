#include "render.hpp"

const sf::Color ceiling_colour(0x73c1c6FF);
const sf::Color floor_colour(0xa79ab2FF);
const double FOV = 70.0 * M_PI / 180.0;
const double depth = (double)X_DIM / 2.0 / tan(FOV / 2.0);

void render(sf::Image& image, Player* player) {
	// ceiling/floor
	for (int x = 0; x < X_DIM; x++) {
		for (int y = 0; y < Y_DIM; y++) {
			image.setPixel(x, y, ceiling_colour);
		}
		for (int y = Y_DIM / 2; y < Y_DIM; y++) {
			image.setPixel(x, y, floor_colour);
		}
	}

	Position pos = player->getPosition();

	for (int x = 0; x < X_DIM; ++x) {
		double tanVal = (double)(X_DIM / 2 - x) / depth;
		double rayAngleOffset = atan(tanVal);
		double rayAngle = fmod(pos.angle + rayAngleOffset + 2.0 * M_PI, 2.0 * M_PI);
		double xOffset;
		std::pair<Node*, double> ray = pos.node->castRay(pos.offset, rayAngle, 0.0, &xOffset);
		Node* wall = ray.first;
		double dist = ray.second;
	
		// TODO: do something about fish lensing

		if (wall == nullptr || wall->getTexture() == nullptr) {
			continue;
		}
		double originalWallHeight = ((double)X_DIM / dist);
		int screenWallHeight = ((int)originalWallHeight > Y_DIM) ? Y_DIM : (int)originalWallHeight;
		for (int y = Y_DIM / 2 - screenWallHeight / 2; y < Y_DIM / 2 + screenWallHeight / 2; ++y) {
			double tx = xOffset;
			double ty = ((double)((double)y + 0.5 - (double)Y_DIM / 2) / originalWallHeight) + 0.5;
			sf::Color colour = wall->getTexture()->data[(size_t)(ty * wall->getTexture()->height)][(size_t)(tx * wall->getTexture()->width)];
			image.setPixel(x, y, colour);
		}
	}
}