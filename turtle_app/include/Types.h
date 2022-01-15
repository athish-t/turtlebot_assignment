#pragma once

#include <queue>
#include <vector>

struct Goal {
	int id;
	std::array<double, 3> coordinates;
};

using Goals = std::queue<Goal>;