#include "node.hpp"

const double renderDistance = 64.0;

Node::Node(bool wall, Texture* texture) : wall(wall), texture(texture), neighbours{ nullptr, nullptr, nullptr, nullptr } {}
Node::~Node() {}

void Node::addNeighbour(Direction direction, Node* neighbour) {
	this->neighbours[(size_t)direction] = neighbour;
}

void Node::removeNeighbour(Direction direction) {
	this->neighbours[(size_t)direction] = nullptr;
}

Node* Node::getNeighbour(Direction direction) {
	return this->neighbours[(size_t)direction];
}

bool Node::isWall() {
	return this->wall;
}

Texture* Node::getTexture() {
	return this->texture;
}

std::pair<Node*, double> Node::castRay(std::complex<double> start, double angle, double distanceSoFar, double* xOffset) {
	// raytrace wall
	if (this->wall) {
		if (start.real() == 0.0) *xOffset = 1.0 - start.imag();
		if (start.real() == 1.0) *xOffset = start.imag();
		if (start.imag() == 0.0) *xOffset = start.real();
		if (start.imag() == 1.0) *xOffset = 1.0 - start.real();
		return { this, distanceSoFar };
	}
	// going through node, phase angle
	else {
		double fi1 = fmod(std::arg(std::complex<double>(1.0, 1.0) - start) + 2.0 * M_PI, 2.0 * M_PI);
		double fi2 = fmod(std::arg(std::complex<double>(0.0, 1.0) - start) + 2.0 * M_PI, 2.0 * M_PI);
		double fi3 = fmod(std::arg(std::complex<double>(0.0, 0.0) - start) + 2.0 * M_PI, 2.0 * M_PI);
		double fi4 = fmod(std::arg(std::complex<double>(1.0, 0.0) - start) + 2.0 * M_PI, 2.0 * M_PI);
		std::complex<double> newStart;
		double d = 0.0;
		Node* neighbour = nullptr;
		// up
		if (angle >= fi1 && angle <= fi2) {
			double h = 1.0 - start.imag();
			double e = h / tan(angle);
			d = h / sin(angle);
			newStart = std::complex<double>(start.real() + e, 0.0);
			neighbour = this->getNeighbour(Direction::UP);
		}
		// left
		else if (angle >= fi2 && angle <= fi3) {
			double h = start.real();
			double e = h * tan(angle);
			d = -(h / cos(angle));
			newStart = std::complex<double>(1.0, start.imag() - e);
			neighbour = this->getNeighbour(Direction::LEFT);
		}
		// down
		else if (angle >= fi3 && angle <= fi4) {
			double h = start.imag();
			double e = h / tan(angle);
			d = -(h / sin(angle));
			newStart = std::complex<double>(start.real() - e, 1.0);
			neighbour = this->getNeighbour(Direction::DOWN);
		}
		// right
		else {
			double h = 1.0 - start.real();
			double e = h * tan(angle);
			d = h / cos(angle);
			newStart = std::complex<double>(0.0, start.imag() + e);
			neighbour = this->getNeighbour(Direction::RIGHT);
		}
		double newDistanceSoFar = distanceSoFar + d;
		if (neighbour == nullptr || newDistanceSoFar > renderDistance) {
			return { nullptr, -1.0 };
		}
		else {
			return neighbour->castRay(newStart, angle, newDistanceSoFar, xOffset);
		}
	}
}
