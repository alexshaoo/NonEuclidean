#pragma once

// for constants like M_PI
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <complex>
#include <stdexcept>

const int X_DIM = 192;
const int Y_DIM = 108;
const int scale = 5;
const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 16;

const double PLAYER_ROTATION = 0.04;
const double PLAYER_MOVE_DISTANCE = 0.05;

const std::vector<std::string> level = {
	"..............x...............",
	"..............x...............",
	"..............x.BBBBBBBBBBBBB.",
	"......RRR.....x.B...........B.",
	"......RRR.....x.B...........B.",
	"......R.R.....x.B..Y..Y..Y..B.",
	"..............x.B...........B.",
	"..............x.B...........B.",
	"..............x.B..Y.....Y..B.",
	"..............x.B...........B.",
	"...GGG.GGG....x.B...........B.",
	"...GG...GG....x.BBBBBB.BBBBBB.",
	"...G.....G....x...............",
	"...GGGGGGG....x...............",
	"..............x...............",
	"..............x..............." 
};
