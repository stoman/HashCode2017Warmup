#pragma once
#include "util.cpp"
#include <cmath>

const int ROTATION = -15;
const int LOW_LAT = -324000; 
const int UP_LAT = 324000;
const int LOW_LON = -648000;
const int UP_LON = 647999;
const int INTERV_LON = UP_LON - LOW_LON;
const int INVER_LAT = UP_LAT - LOW_LAT;


double checkBounds_x(double x)
{
	if (x < LOW_LON)
		return x + INTERV_LON;
	else if (x > LOW_LON)
		return x - INTERV_LON;
	return x;
}

double projectUp(ll x, ll y, double v, int x_speed)
{
	double t = 1.0 * (UP_LON - y) / abs(v);
	double pos = x + t * x_speed;
	return checkBounds_x(pos);
}


double projectDown(ll x, ll y, double v, int x_speed)
{
	double t = 1.0 * (y - LOW_LON) / abs(v);
	double pos = x + t * x_speed;
	return checkBounds_x(pos);
}


double distX(double x1, double x2)
{
	if (x1 > x2)
		swap(x1, x2);
	return min(x2 - x1, x1 - LOW_LON + UP_LON - x2);
}


//return intervals during which the satellite can photograph the object
//ignoring the photos the satellite should already take
vector<pair<ll, ll>> possible_intervals(Input& input, Satellite& satellite, Object& object) 
{
	double crossTime = 1.0 * INVER_LAT / abs(satellite.v);
	double crossLen = crossTime * ROTATION;

	vector<double> up_positions;
	vector<double> down_positions;
	vector<double> up_times;
	vector<double> down_times;
	
	bool isUp;
	double time;
	double len;
	if (satellite.v > 0)
	{
		len = projectUp(satellite.lon, satellite.lat, satellite.v, ROTATION);
		up_positions.push_back(len);
		time = (UP_LAT - satellite.lat) / satellite.v;
		up_times.push_back(time);
		isUp = true;	
	}
	else
	{
		len = projectDown(satellite.lon, satellite.lat, satellite.v, ROTATION);
		down_positions.push_back(len);
		time = (satellite.lat - LOW_LAT) / satellite.v;
		down_times.push_back(time);
		isUp = false;
	}

	while (time + crossTime < input.t)
	{
		time += crossTime;
		len = checkBounds_x(len + crossLen);
		isUp = !isUp;

		if (isUp)
		{
			up_positions.push_back(len);
			up_times.push_back(time);
		}
		else
		{
			down_positions.push_back(len);
			down_times.push_back(time);
		}
	}



	// project object
	double obj_up_pos = projectUp(object.lon, object.lat, satellite.v, -ROTATION);
	double obj_down_pos = projectDown(object.lon, object.lat, satellite.v, ROTATION);

	vector<pair<ll, ll>> intervals;
	for (int i = 0; i < up_positions.size(); i++)
	{
		if (distX(obj_up_pos, up_positions[i]) < satellite.d)
		{
			double t_star = up_times[i] + 1.0 * (UP_LAT - object.lat) / satellite.v;
			intervals.push_back(make_pair(floor(t_star), ceil(t_star)));
		}
	}

	for (int i = 0; i < down_positions.size(); i++)
	{
		if (distX(obj_down_pos, down_positions[i]) < satellite.d)
		{
			double t_star = down_times[i] + 1.0 * (object.lat - LOW_LAT) / satellite.v;
			intervals.push_back(make_pair(floor(t_star), ceil(t_star)));
		}
	}

	return intervals;
}



