#pragma once
#include "util.cpp"

//util classes
/*struct Object {
	long long lon, lat;
	bool done;
	int collection_id;
};

struct Satellite {
	long long lon, lat, v, w, d;
	map<long long, Object> photos;
};*/


void compute_satellite_coordinates(pair<ll,ll> &coor, Satellite &satellite, ll time)	{
	ll lat_max =  90ll*3600ll;
	ll lon_max = 180ll*3600ll;
	
	ll lat = (satellite.lat + lat_max + time*satellite.v) % (2ll*lat_max+1ll); // from -90 deg to 90 deg inclusive
	ll lon = (satellite.lon + lon_max + time*15ll) % (2ll*lon_max);
	
	lat -= lat_max;
	lon -= lon_max;
	
	coor.first = lat_max;
	coor.second = lon_max;
}

void compute_satellite_angles(pair<ll,ll> &angles, pair<ll,ll> &coor, Object &object)	{
	angles.first  =  coor.first - object.lat;
	angles.second = coor.second - object.lon;
}

bool check_angles(pair<ll,ll> &angle_change, ll time, ll angular_speed)	{
	return (abs(angle_change.first) <= time*angular_speed) && (abs(angle_change.second) <= time*angular_speed);
}

//can the satellite take a photo of the given object at the given time with
//regard to the photos the satellite already takes
bool photo_fits_schedule(Input& input, Satellite& satellite, Object& object, ll time) {
	if (satellite.photos.empty())
		return true;
	
	pair <ll, ll> cur_coor, prev_coor, next_coor;
	pair <ll, ll> cur_angle, prev_angle, next_angle;
	pair <ll, ll> angle_change;
	
	compute_satellite_coordinates(cur_coor,satellite,time);
	compute_satellite_angles(cur_angle,cur_coor,object);
	
	map<ll,Object>::iterator ub;
	ub = satellite.photos.upper_bound(time);
	
	bool fits = true;
	
	if (ub != satellite.photos.begin())	
	{
		ub--;
		compute_satellite_coordinates(prev_coor,satellite,ub->first);
		compute_satellite_angles(prev_angle,prev_coor,object);	
		angle_change.first = cur_angle.first - prev_angle.first;
		angle_change.second = cur_angle.second - prev_angle.second;
		fits = fits & check_angles(angle_change,time - ub->first,satellite.w);
		ub++;
	}
	
	if (ub != satellite.photos.end())
	{
		compute_satellite_coordinates(next_coor,satellite,ub->first);
		compute_satellite_angles(next_angle,next_coor,object);
		angle_change.first = cur_angle.first - prev_angle.first;
		angle_change.second = cur_angle.second - prev_angle.second;
		fits = fits & check_angles(angle_change,ub->first - time,satellite.w);
	}
	return fits;
}
