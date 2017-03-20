#pragma once
#include "util.cpp"
#include <set>


struct Coord {
	int r, c, h;
};

bool operator < (const Coord &a, const Coord &b)	{
	if (a.r != b.r)
		return a.r < b.r;
	else if (a.c != b.c)
		return a.c < b.c;
	else
		return a.h < b.h;
}

void check_cell(Input &input, Coord cur, vector<Coord>& path, vector<int>& prev, set<Coord>& visited, vector<int>& dist, int idx)	{

	//cerr << "adding balloon: " << cur.r << ' ' << cur.c << ' ' << cur.h << endl;	
	
	int dr = input.movement_r[cur.r][cur.c][cur.h];
	int dc = input.movement_c[cur.r][cur.c][cur.h];
	cur.r += dr;
	cur.c += dc;
	cur.c = (cur.c + input.c) % input.c;	

	//cerr << "done\n";

	if (visited.find(cur) != visited.end())
		return;		
	path.push_back(cur);
	prev.push_back(idx);
	dist.push_back(dist[idx]+1);
	visited.insert(cur);
}

void bfs(Input &input, vector<Coord>& path, vector<int>& prev)	{
	
	set<Coord> visited;
	vector<int> dist;
	int idx = 0;
	dist.push_back(idx);
	visited.insert(path[idx]);
	
	while (idx < path.size())	{
		Coord cur = path[idx];
		
		//cerr << "current balloon: " << cur.r << ' ' << cur.c << ' ' << cur.h << endl;
		
		if (dist[idx] > 5)
			break;
		
		// out of bounds -> stay there
		if (cur.r >= input.r || cur.r < 0)	{
			path.push_back(cur);
			prev.push_back(idx);
			dist.push_back(dist[idx]+1);
		}
		
		// try changing the altitude
		else	{
			check_cell(input,cur,path,prev,visited,dist,idx);
			
			if (cur.h > 1)
			{
				cur.h--;
				check_cell(input,cur,path,prev,visited,dist,idx);
				cur.h++;
			}
			
			if (cur.h < input.a)	
			{
				cur.h++;
				check_cell(input,cur,path,prev,visited,dist,idx);
				cur.h--;
			}	
		}
		idx++;
	}
}

void pathfinding(Input& input, int balloon, double r, double c, int delta) {
	//TODO fill me
	vector<Coord> path;
	vector<int> prev;
	
	// add starting cell
	Coord start;
	start.r = input.balloons[balloon].r.back();
	start.c = input.balloons[balloon].c.back();
	start.h = input.balloons[balloon].h.back();
	
	path.push_back(start);
	prev.push_back(-1);
	
	//run bfs
	bfs(input,path,prev);
	
	// choose the closest end point
	double mind = 1e9, curd;
	int idx_min = 1;
	for (int i = 0; i < path.size(); i++)
	{
		curd = ((double)path[i].r-r)*((double)path[i].r-r) + ((double)path[i].c-c)*((double)path[i].c-c);
		if (curd < mind)
		{
			idx_min = i;
			mind = curd;
		}
	}

	vector<Coord> reversed_path;
	for (int i = idx_min; i != 0; i = prev[i])
		reversed_path.push_back(path[i]);
	
	/*cerr << "flying from: " << start.r << ' ' << start.c << ' ' << start.h << endl;
	cerr << "path\n";
	for (int i = reversed_path.size()-1; i >= 0; i--)
		cerr << reversed_path[i].r << ' ' << reversed_path[i].c << ' ' << reversed_path[i].h << endl; 
	cerr << "end of path\n";*/
	
	for (int i = reversed_path.size()-1; i >= 0; i--)
	{
		input.balloons[balloon].h.push_back(reversed_path[i].h);
		input.balloons[balloon].r.push_back(reversed_path[i].r);
		input.balloons[balloon].c.push_back(reversed_path[i].c);
		
		if (input.balloons[balloon].h.size() > input.t)
			break;
	}
}
