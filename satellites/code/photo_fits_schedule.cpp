#pragma once
#include "util.cpp"



void compute_satellite_coordinates(pair<ll,ll> &coor, const Satellite &satellite, ll time)	{
	ll lat_max =  90ll*3600ll;
	ll lon_max = 180ll*3600ll;
	
	ll lat = (satellite.lat + lat_max + time*satellite.v) % (2ll*lat_max+1ll); // from -90 deg to 90 deg inclusive
	ll lon = (satellite.lon + lon_max + time*15ll) % (2ll*lon_max);
	
	lat -= lat_max;
	lon -= lon_max;
	
	coor.first = lat_max;
	coor.second = lon_max;
}

void compute_satellite_angles(pair<ll,ll> &angles, const pair<ll,ll> &coor, const Object &object)	{
	angles.first  =  coor.first - object.lat;
	angles.second = coor.second - object.lon;
}

void compute_satellite_angle_change(pair<ll,ll> &angle_change, const pair<ll,ll> &next_angle, const pair<ll,ll> &cur_angle){
	angle_change.first  = next_angle.first  - cur_angle.first;
	angle_change.second = next_angle.second - cur_angle.second;
}

bool check_angular_speed(const pair<ll,ll> &angle_change, ll time, ll angular_speed)	{
	return (abs(angle_change.first) <= time*angular_speed) && (abs(angle_change.second) <= time*angular_speed);
}

bool check_angle(const pair<ll,ll> &angle, const ll max_angle)	{
	return (abs(angle.first) <= max_angle) && (abs(angle.second) <= max_angle);
}

//can the satellite take a photo of the given object at the given time with
//regard to the photos the satellite already takes
bool photo_fits_schedule(Input& input, Satellite& satellite, Object& object, ll time) {

	pair <ll, ll> cur_coor, prev_coor, next_coor;
	pair <ll, ll> cur_angle, prev_angle, next_angle;
	pair <ll, ll> angle_change;
	
	compute_satellite_coordinates(cur_coor,satellite,time);
	compute_satellite_angles(cur_angle,cur_coor,object);
	
	bool fits = check_angle(cur_angle,satellite.d);

	if (satellite.photos.empty())
		return fits;
	
	map<ll,Object>::iterator ub;
	ub = satellite.photos.upper_bound(time);

	if (ub != satellite.photos.begin())	
	{
		ub--;
		
		compute_satellite_coordinates(prev_coor,satellite,ub->first);
		compute_satellite_angles(prev_angle,prev_coor,ub->second);	
		
		compute_satellite_angle_change(angle_change,cur_angle,prev_angle);
		
		fits = fits & check_angular_speed(angle_change,time - ub->first,satellite.w);
		
		ub++;
	}
	
	if (ub != satellite.photos.end())
	{
		compute_satellite_coordinates(next_coor,satellite,ub->first);
		compute_satellite_angles(next_angle,next_coor,ub->second);
		
		compute_satellite_angle_change(angle_change,next_angle,cur_angle);
		
		fits = fits & check_angular_speed(angle_change,ub->first - time,satellite.w);
	}
	return fits;
}
