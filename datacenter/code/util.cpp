#ifndef utils
#define utils

#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>
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

//input handling
bool compareById(const Server &a, const Server &b) {
  return a.id < b.id;
}

void readInput(Input& input, istream& in) {
	in >> input.r >> input.s >> input.u >> input.p >> input.m;
	input.blocked_slots.resize(input.r);
	for(int i = 0; i < input.u; i++) {
		int r, s;
		in >> r >> s;
		input.blocked_slots[r].push_back(s);
	}
	for(int i = 0; i < input.m; i++) {
		int z, c;
		in >> z >> c;
		Server server;
		server.id = i;
		server.capacity = c;
		server.size = z;
		input.servers.push_back(server);
	}
}

#endif
