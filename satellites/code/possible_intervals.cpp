#pragma once
#include "util.cpp"

//return intervals during which the satellite can photograph the object
//ignoring the photos the satellite should already take
vector<pair<ll, ll>> possible_intervals(Input& input, Satellite& satellite, Object& object) {
	vector<pair<ll, ll>> ret(1);
	ret[0] = make_pair(0, input.t-1);
	return ret;
}
