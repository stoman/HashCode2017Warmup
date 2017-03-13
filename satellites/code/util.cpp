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
	ll lat, lon;
	bool done;
	vector<int> collections;

	Object(ll lat, ll lon): lat(lat), lon(lon), done(false) {};
	Object() {};
};

struct Collection {
	ll v, r;
	int l;
	int id;
	bool done;
	vector<Object> objects;
	vector<pair<ll, ll>> time_ranges;

	Collection(ll v, int l, ll r, int id): v(v), l(l), r(r), id(id), done(false) {};
	Collection() {};
};

struct Satellite {
	ll lat, lon, v, w, d;
	map<ll, Object> photos;

	Satellite(ll lat, ll lon, ll v, ll w, ll d): lat(lat), lon(lon), v(v), w(w), d(d) {};
};

struct Input {
	ll t;
	int s, c;
	vector<Satellite> satellites;
	vector<Collection> collections;
	map<pair<ll, ll>, Object> objects;
};

//input handling
void readInput(Input& input, istream& in) {
	in >> input.t >> input.s;
	for(int i = 0; i < input.s; i++) {
		ll lat, lon, v, w, d;
		in >> lat >> lon >> v >> w >> d;
		input.satellites.push_back(*(new Satellite(lat, lon, v, w, d)));
	}
	in >> input.c;
	for(int i = 0; i < input.c; i++) {
		int l;
		ll v, r;
		in >> v >> l >> r;
		input.collections.push_back(*(new Collection(v, l, r, i)));
		for(int j = 0; j < l; j++) {
			ll lat, lon;
			in >> lat >> lon;
			if(input.objects.find(make_pair(lat, lon)) == input.objects.end()) {
				input.objects[make_pair(lat, lon)] = *(new Object(lat, lon));
			}
			input.objects[make_pair(lat, lon)].collections.push_back(i);
			input.collections[i].objects.push_back(input.objects[make_pair(lat, lon)]);
		}
		for(int j = 0; j < r; j++) {
			ll ts, te;
			in >> ts >> te;
			input.collections[i].time_ranges.push_back(make_pair(ts, te));
		}
	}
}
