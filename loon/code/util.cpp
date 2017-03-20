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
#include <queue>

using namespace std;

//util classes
struct Cluster {
	int center_r, center_c, id;
	vector<pair<int, int>> cells;
};

struct Balloon {
	int id, cluster_id;
	vector<int> r, c, h;
};

struct Input {
	int r, c, a, l, v, b, t, rs, cs;
	vector<Cluster> clusters;
	vector<Balloon> balloons;
	vector<int> cell_r;
	vector<int> cell_c;
	vector<vector<vector<int>>> movement_r;
	vector<vector<vector<int>>> movement_c;
};

//input handling
void readInput(Input& input, istream& in) {
	
	
}













