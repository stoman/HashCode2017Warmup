#pragma once
#include "util.cpp"

/*
struct Cluster {
	int rx, cy, id;
	vector<pair<int, int>> cells;
};

struct Balloon {
	int id, cluster_id;
	vector<int> r, c, h;
};

struct Input {
	int r, c, a, l, v, b, t, rs, cs;
	vector<Cluster> clusters;
	vector<Ballon> balloon;
	vector<int> cell_x;
	vector<int> cell_y;
	vector<vector<vector<int>>> movement_x;
	vector<vector<vector<int>>> movement_y;
};

struct Coord {
	int r, c, h;
};

void bfs(Input &input, vector<Coord> path)	{
	
	while (!q.empty())	{
		Coord cur = q.front();
		path.insert()
		if (cur.r >= input.r || cur.r < 0)	{
			cur.r = 
		}
	}
}*/

void pathfinding(Input& input, int balloon, int r, int c, int delta) {
	//TODO fill me
	//queue<Coord> q;
	//Coord start;
	int rr = input.balloons[balloon].r.back();
	int cc = input.balloons[balloon].c.back();
	//int hh = input.balloons[balloon].h.back();
	
	//q.push(start);
	
	input.balloons[balloon].h.push_back(1);
	
	input.balloons[balloon].r.push_back(r+input.movement_r[rr][cc][1]);
	input.balloons[balloon].c.push_back(c+input.movement_c[rr][cc][1]);
	//bfs(input,q);
}
