#ifndef utils
#define utils

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
	long long lon, lat;
	bool done;
	int collection_id;
};

struct Collection {
	long long v, l, r;
	int id;
	bool done;
	vector<Object> objects;
	vector<pair<long long, long long>> time_ranges;
};

struct Satellite {
	long long lon, lat, v, w, d;
	map<long long, Object> photos;
};

struct Input {
	long long t;
	int s, c;
	vector<Satellite> satellites;
	vector<Collection> collections;
};

//input handling
void readInput(Input& input, istream& in) {
	//TODO read input
}

#endif
