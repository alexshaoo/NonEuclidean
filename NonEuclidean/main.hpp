#pragma once

// for constants like M_PI
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <complex>
#include <stdexcept>

const int X_DIM = 320;
const int Y_DIM = 180;
const int scale = 5;
const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 16;

const double MOUSE_SENSITIVITY = 0.0005;
const double PLAYER_MOVE_DISTANCE = 0.05;

// Level 1: Portal Basics - Introduction to non-euclidean portals
const std::vector<std::string> level1 = {
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

// Level 2: The Impossible Loop - Walk in a square and end up elsewhere
const std::vector<std::string> level2 = {
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
	"R............................R",
	"R.BBBBBBBBBBBB..YYYYYYYYYYYY.R",
	"R.B..........B..Y..........Y.R",
	"R.B..........B..Y..........Y.R",
	"R.B..........B..Y..........Y.R",
	"R.B..........B..Y..........Y.R",
	"R.B..........B..Y..........Y.R",
	"R.B..........BBBY..........Y.R",
	"R.B.......................GY.R",
	"R.B.GGGGGGGGGGGGGGGGGGGGGGGY.R",
	"R.B.G......................Y.R",
	"R.BBB......................Y.R",
	"R..........................Y.R",
	"R.YYYYYYYYYYYYYYYYYYYYYYYYYY.R",
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
};

// Level 3: Bigger on the Inside - TARDIS effect
const std::vector<std::string> level3 = {
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
	"R............................R",
	"R............................R",
	"R............................R",
	"R..........BBBB..............R",
	"R..........B..B..............R",
	"R..........B..B..............R",
	"R..........BBBB..............R",
	"R............................R",
	"R............................R",
	"RGGGGGGGGGGGGGGGGGGGGGGGGGGGGR",
	"RG..........................GR",
	"RG..YYYYYYYYYYYYYYYYYYYYYY..GR",
	"RG..Y....................Y..GR",
	"RG..YYYYYYYYYYYYYYYYYYYYYY..GR",
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
};

// Level 4: The Mirror Maze - Left and right are the same space
const std::vector<std::string> level4 = {
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
	"R............BB............BBR",
	"R...........B..B..........B..R",
	"R..........B....B........B...R",
	"R.........B......B......B....R",
	"R........BYYYYYYYYYYYYYB.....R",
	"R.......BY..............B....R",
	"R.......Y................B...R",
	"R.......Y.................B..R",
	"R.......Y..................B.R",
	"R.......Y..................B.R",
	"R.......Y.................B..R",
	"R.......BY...............B...R",
	"R........BYYYYYYYYYYYYYB.....R",
	"R.........BBBBBBBBBBBB.......R",
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
};

// Level 5: The Escher Staircase - Penrose stairs
const std::vector<std::string> level5 = {
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
	"R...........BBBBB............R",
	"R...........B...B............R",
	"R...GGGGGGGGG...BBBBBBBBB....R",
	"R...G...................B....R",
	"R...G...................B....R",
	"YYYYG...................BYYYYY",
	"R...G...................B....R",
	"R...G...................B....R",
	"R...GGGGGGGGGGGGGGGGGGGGG....R",
	"R............................R",
	"R............................R",
	"R....BBBBBBBBBBBBBBBBBBBB....R",
	"R....B..................B....R",
	"R....BBBBBBBBBBBBBBBBBBBB....R",
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
};

// Level 6: Recursive Rooms - A room that contains itself
const std::vector<std::string> level6 = {
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
	"R..BBBB..........BBBB........R",
	"R..B..B..........B..B........R",
	"R..B..BGGGGGGGGGGG..BGGGGGGGGR",
	"R..B..BG..........BBG........R",
	"R..BBBGG..........BBB........R",
	"R.....BG.....................R",
	"R.....BG.....................R",
	"R.....BG..YYY..YYY..YYY......R",
	"R.....BG..Y.Y..Y.Y..Y.Y......R",
	"R.....BG..YYY..YYY..YYY......R",
	"R.....BG.....................R",
	"R.....BGGGGGGGGGGGGGGGGGGGGGGR",
	"R.....B......................R",
	"R.....BBBBBBBBBBBBBBBBBBBBBBBR",
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
};
