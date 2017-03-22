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
#include <queue>

using namespace std;

//util classes
struct Cluster {
	double center_r, center_c;
	int id;
	vector<pair<int, int>> cells;
};

struct Balloon {
	int id, cluster_id;
	vector<int> r, c, h;
};

struct Input {
	int r, c, a, l, v, b, t, rs, cs;
	vector<Cluster> clusters;
	vector<Balloon> balloons;
	vector<int> cell_r;
	vector<int> cell_c;
	vector<vector<vector<int>>> movement_r;
	vector<vector<vector<int>>> movement_c;
	vector<vector<int>> cell_field;
};

//input handling
void readInput(Input& input, istream& in) {
	in >> input.r >> input.c >> input.a;
	in >> input.l >> input.v >> input.b >> input.t;
	in >> input.rs >> input.cs;
	for (int i = 0; i < input.l; ++i)
	{
		int ri, ci;
		in >> ri >> ci;
		input.cell_r.push_back(ri);
		input.cell_c.push_back(ci);
	}


	// resize movement
	input.movement_r.resize(input.r);
	input.movement_c.resize(input.r);
	for (int i = 0; i < input.r; ++i)
	{
		input.movement_r[i].resize(input.c);
		input.movement_c[i].resize(input.c);

		for (int j = 0; j < input.c; ++j)
		{
			input.movement_r[i][j].resize(input.a+1);
			input.movement_c[i][j].resize(input.a+1);
		}
	}

	// set movements of altitude level 0 to (0,0)
	for (int r = 0; r < input.r; ++r)
	{
		for (int c = 0; c < input.c; ++c)
		{
			input.movement_r[r][c][0] = 0;
			input.movement_c[r][c][0] = 0;
		}
	}


	for (int a = 1; a <= input.a; ++a)
	{
		for (int r = 0; r < input.r; ++r)
		{
			for (int c = 0; c < input.c; ++c)
			{
				int dr, dc;
				in >> dr >> dc;
				input.movement_r[r][c][a] = dr;
				input.movement_c[r][c][a] = dc;
			}
		}
	}

	// set start coordinates as first coordinate of every balloon
	input.balloons.resize(input.b);
	for (int b = 0; b < input.b; ++b)
	{
		input.balloons[b].r.push_back(input.rs);
		input.balloons[b].c.push_back(input.cs);
		input.balloons[b].h.push_back(0);
	}

	// initialize cell field
	input.cell_field.resize(input.r);
	for (int i = 0; i < input.r; ++i)
		input.cell_field[i].resize(input.c, 0);
	for (int i = 0; i < input.cell_r.size(); ++i)
		input.cell_field[input.cell_r[i]][input.cell_c[i]] = 1;
}













