#pragma once
#include "util.cpp"
#include "photo_fits_schedule.cpp"
#include "possible_intervals.cpp"


bool try_photo(Input& input, Object& object, Collection& collection) {
	//is already done? You could have figured that out yourself, don't you?!
	if(input.objects[make_pair(object.lat, object.lon)].done) {
		return true;
	}
	//loop over satellites
	for(Satellite& satellite: input.satellites) {
		vector<pair<ll, ll>> intervals = possible_intervals(input, satellite, object);
		for(pair<ll, ll>& time_range: collection.time_ranges) {
			for(pair<ll, ll> interval: intervals) {
				for(ll time = max(interval.first, time_range.first); time < min(interval.second, time_range.second); time+=1000) {
					if(photo_fits_schedule(input, satellite, object, time)) {
						input.objects[make_pair(object.lat, object.lon)].done = true;
						satellite.photos[time] = object;
						return true;
					}
				}
			}
		}
	}
	return false;
}

//start of the algorithm, call all subroutines
void schedule_photos(Input& input) {
    cerr << "Starting scheduling"
	vector<Collection> sorted_collections(input.c);
	for(int i = 0; i < input.c; i++) {
		sorted_collections[i] = input.collections[i];
	}
	sort(sorted_collections.begin(), sorted_collections.end(), [](const Collection& lhs, const Collection& rhs) {
   		return lhs.v/lhs.l > rhs.v/rhs.l;
	});

	//try them all
	for(Collection& collection: sorted_collections) {
        cerr << "Considering collection " << collection.id << "/" << input.c;
		bool ok = true;
		for(Object& object: collection.objects) {
			ok &= try_photo(input, object, collection);
		}
		input.collections[collection.id].done = ok;
		//todo remove photos if collection not finished
	}
}
