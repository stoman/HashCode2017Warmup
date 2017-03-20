#pragma once

typedef long long ll;

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <time.h>
#include <utility>
#include <vector>

using namespace std;

//util classes
struct Cluster {
	int rx, cy, id;
	vector<pair<int, int>> cells;
};

struct Balloon {
	int id, cluster_id;
	vector<int> r, c, h;
};

struct Input {
	int r, c, a, l, v, b, t, rs, cs;
	vector<Cluster> clusters;
	vector<Ballon> balloon;
};

//input handling
void readInput(Input& input, istream& in) {
	//TODO read input
}
