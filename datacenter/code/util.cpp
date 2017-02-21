#ifndef utils
#define utils

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//util classes
struct Server {
	//input
	int capacity, size, id;
	//output
	int row = -1, slot = -1, pool = -1;
};

struct Input {
	int r, s, u, p, m;
	vector<vector<int>> blocked_slots;//first index: row, second index: slot
	vector<Server> servers;
};

#endif
