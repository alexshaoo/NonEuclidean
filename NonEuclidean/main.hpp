#pragma once

// for constants like M_PI
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <complex>
#include <stdexcept>

const int x_dim = 192;
const int y_dim = 108;
const int scale = 5;

const std::vector<std::string> level = {
	"..............x...............", // 0
	"..............x...............", // 1
	"..............x.BBBBBBBBBBBBB.", // 2
	"......RRR.....x.B...........B.", // 3
	"......RRR.....x.B...........B.", // 4
	"......R.R.....x.B..Y..Y..Y..B.", // 5
	"..............x.B...........B.", // 6
	"..............x.B...........B.", // 7
	"..............x.B..Y.....Y..B.", // 8
	"..............x.B...........B.", // 9
	"...GGG.GGG....x.B...........B.", // 10
	"...GG...GG....x.BBBBBB.BBBBBB.", // 11
	"...G.....G....x...............", // 12
	"...GGGGGGG....x...............", // 13
	"..............x...............", // 14
	"..............x..............."  // 15
};
