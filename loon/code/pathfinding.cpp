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

	if (r1 < 0 || r1 >= r || r2 < 0 || r2 >= r)
		return 1e12;

	double dr = abs(r1-r2);
	double dc = min(abs(c1-c2),c-abs(c1-c2));
	return sqrt(dr*dr+dc*dc);
}

void check_cell(Input &input, Coord cur, vector<Coord>& path, vector<int>& prev, set<Coord>& visited, vector<int>& dist, 
					int idx, double r, double c)	{

	int dr = input.movement_r[cur.r][cur.c][cur.h];
	int dc = input.movement_c[cur.r][cur.c][cur.h];
	cur.r += dr;
	cur.c += dc;
	cur.c = (cur.c + input.c) % input.c;	
	
	//double dinit = compute_distance(path[0].r,path[0].c,r,c,input.r,input.c);
	//double dcur =  compute_distance(    cur.r,    cur.c,r,c,input.r,input.c);

	if (visited.find(cur) != visited.end())// || (dinit+20. < dcur && path.size() > 1))
		return;		
	path.push_back(cur);
	prev.push_back(idx);
	dist.push_back(dist[idx]+1);
	visited.insert(cur);
}

void bfs(Input &input, vector<Coord>& path, vector<int>& prev, double r, double c, int bfsdepth)	{
	
	set<Coord> visited;
	vector<int> dist;
	int idx = 0;
	dist.push_back(0);
	visited.insert(path[idx]);
	
	while (idx < path.size())	{
		Coord cur = path[idx];
		
		//cerr << "current balloon: " << cur.r << ' ' << cur.c << ' ' << cur.h << endl;
		
		if (dist[idx] > bfsdepth)
			break;
		
		//if (path.size() > 10000)
		//	break;
		
		// out of bounds -> stay there
		if (cur.r >= input.r || cur.r < 0)	{
			path.push_back(cur);
			prev.push_back(idx);
			dist.push_back(dist[idx]+1);
		}
		
		// fly on neighboring altitudes
		else	{
			check_cell(input,cur,path,prev,visited,dist,idx,r,c);
			
			if (cur.h > 1)
			{
				cur.h--;
				check_cell(input,cur,path,prev,visited,dist,idx,r,c);
				cur.h++;
			}
			
			if (cur.h < input.a)	
			{
				cur.h++;
				check_cell(input,cur,path,prev,visited,dist,idx,r,c);
				cur.h--;
			}	
		}
		idx++;
	}
}

void append_path(Input& input, int balloon, vector<Coord>& path, vector<int>& prev, int idx_min)	{

	vector<Coord> reversed_path;
	for (int i = idx_min; i != 0; i = prev[i])
		reversed_path.push_back(path[i]);

	for (int i = reversed_path.size()-1; i >= 0; i--)
	{
		input.balloons[balloon].h.push_back(reversed_path[i].h);
		input.balloons[balloon].r.push_back(reversed_path[i].r);
		input.balloons[balloon].c.push_back(reversed_path[i].c);

		if (input.balloons[balloon].h.size() > input.t)
			break;
	}
	
}

int choose_closest_point(Input &input, vector<Coord>& path, double r, double c) 	{
	double mind = 1e10, curd;
	int idx_min = 0;
	for (int i = 1; i < path.size(); i++)
	{
		curd = compute_distance(path[i].r,path[i].c,r,c,input.r,input.c);
		if (curd < mind || idx_min == 0)
		{
			idx_min = i;
			mind = curd;
		}
	}
	
	return idx_min;
}

void pathfinding(Input& input, int balloon, double r, double c, double delta, int bfsdepth, double delta_c) {

	while (input.balloons[balloon].h.size() <= input.t && 
		   compute_distance(input.balloons[balloon].r.back(),input.balloons[balloon].c.back(),r,c,input.r,input.c) > delta &&
		   input.balloons[balloon].c.back() <= c + delta_c)
	{
		vector<Coord> path;
		vector<int> prev;
		// add starting cell
		Coord start;
		
		start.r = input.balloons[balloon].r.back();
		start.c = input.balloons[balloon].c.back();
		start.h = input.balloons[balloon].h.back();
	
		path.push_back(start);
		prev.push_back(-1);
		
		bfs(input,path,prev,r,c,bfsdepth);

		int idx_min = choose_closest_point(input,path,r,c);

		append_path(input,balloon,path,prev,idx_min);
		
	}
	// end of while
	
	// DEBUG OUTPUT	
	/*bool inside = true, arrived = false;
	for (int i = 0; i < input.balloons[balloon].r.size(); i++)
	{
		int rc = input.balloons[balloon].r[i];
		int cc = input.balloons[balloon].c[i];
		if (!arrived && compute_distance(rc,cc,r,c,input.r,input.c) < input.v)
		{
			cerr << "Ballon " << balloon << " has reached the center of its cluster.\n";
			arrived = true;
		}
		
		if (input.balloons[balloon].h[i] > input.a || (input.balloons[balloon].h[i] < 1 && i > 0))
			cerr << "ERROR: balloon " << balloon << " violates the height constraints.\n";
		
		if (cc < 0 || cc >= input.c)
			cerr << "ERROR: coordiantes of balloon " << balloon << " do not satisfy column constraints.\n";
		
		if (inside && (rc < 0 || rc >= input.r))
		{
			cerr << "Ballon " << balloon << " was lost at turn " << i << ".\n"; 
			inside = false;
		}
	}//*/
	
	// VISULAIZATION OF THE PATH
	/*
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
	}*/
}
