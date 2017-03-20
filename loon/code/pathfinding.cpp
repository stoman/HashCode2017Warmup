#pragma once
#include "util.cpp"
#include <set>
#include <cmath>

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

double compute_distance(double r1, double c1, double r2, double c2, double r, double c)	{	
	if (r1 < 0 || r1 >= r)
		return 1e9;

	double dr = abs(r1-r2);
	double dc = min(abs(c1-c2),c-abs(c1-c2));
	return sqrt(dr*dr+dc*dc);
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

void pathfinding(Input& input, int balloon, double r, double c, double delta) {
	//TODO fill me
	//run bfs
	while (input.balloons[balloon].h.size() <= input.t && 
		compute_distance(input.balloons[balloon].r.back(),input.balloons[balloon].c.back(),r,c,input.r,input.c) > delta)
	{
		vector<Coord> path; path.clear();
		vector<int> prev; prev.clear();
		// add starting cell
		Coord start;
		
		start.r = input.balloons[balloon].r.back();
		start.c = input.balloons[balloon].c.back();
		start.h = input.balloons[balloon].h.back();
	
		path.push_back(start);
		prev.push_back(-1);
		
		bfs(input,path,prev);

		// choose the closest end point
		double mind = 1e9, curd;
		int idx_min = 1;
		for (int i = 2; i < path.size(); i++)
		{
			curd = compute_distance(path[i].r,path[i].c,r,c,input.r,input.c);
			if (curd < mind || idx_min == 0)
			{
				idx_min = i;
				mind = curd;
			}
		}

		//cerr << path.size() << endl;
		vector<Coord> reversed_path;
		for (int i = idx_min; i != 0; i = prev[i])
			reversed_path.push_back(path[i]);

		/*
		cerr << "flying from: " << start.r << ' ' << start.c << ' ' << start.h << endl;
		cerr << "to target: " << r << ' ' << c << endl;
		cerr << "path\n";
		for (int i = reversed_path.size()-1; i >= 0; i--)
			cerr << reversed_path[i].r << ' ' << reversed_path[i].c << ' ' << reversed_path[i].h << endl; 
		cerr << "end of path\n";//*/

		for (int i = reversed_path.size()-1; i >= 0; i--)
		{
			input.balloons[balloon].h.push_back(reversed_path[i].h);
			input.balloons[balloon].r.push_back(reversed_path[i].r);
			input.balloons[balloon].c.push_back(reversed_path[i].c);
	
			if (input.balloons[balloon].h.size() > input.t)
				break;
		}
		
		//double endr = input.balloons[balloon].r.back();
		//double endc = input.balloons[balloon].c.back();
		//dist_to_dest = compute_distance(endr,endc,r,c);
	}
	
	for (int i = 0; i < input.balloons[balloon].r.size()-1; i++)
	{
		int rc = input.balloons[balloon].r[i];
		int rn = input.balloons[balloon].r[i+1];
		
		int cc = input.balloons[balloon].c[i];
		int cn = input.balloons[balloon].c[i+1];
		
		if (abs(cc-cn) > input.c - abs(cc-cn))
			cerr << cc << ' ' << rc << ' ' << 0 << ' ' << 0 << ' ' << input.balloons[balloon].cluster_id / ((double)input.clusters.size()) << endl;
		else
			cerr << cc << ' ' << rc << ' ' << cn-cc << ' ' << rn-rc << ' ' << input.balloons[balloon].cluster_id / ((double)input.clusters.size()) << endl;
	}
	cerr << endl;
}
