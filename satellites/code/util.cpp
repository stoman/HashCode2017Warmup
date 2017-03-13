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
struct Object {
	ll lon, lat;
	bool done;
	vector<int> collections;
};

struct Collection {
	ll v, l, r;
	int id;
	bool done;
	vector<Object> objects;
	vector<pair<ll, ll>> time_ranges;
};

struct Satellite {
	ll lon, lat, v, w, d;
	map<ll, Object> photos;
};

struct Input {
	ll t;
	int s, c;
	vector<Satellite> satellites;
	vector<Collection> collections;
};

//input handling
void readInput(Input& input, istream& in) {
	//TODO read input
}
