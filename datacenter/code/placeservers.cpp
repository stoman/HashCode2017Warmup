#include "util.cpp"

/*
//util classes
struct Server {
	//input
	int capacity, size;
	//output
	int row = -1, slot = -1, pool = -1;
};

struct Input {
	int r, s, u, p, m;
	vector<vector<int>> blocked_slots;//first index: row, second index: slot
	vector<Server> servers;
};
*/

struct Row {
	int num, area, capacity;
};

bool sort_servers(const Server &a, const Server &b)	{
	if (a.capacity*b.size != b.capacity*a.size)
		return a.capacity*b.size > b.capacity*a.size;
	else
		return a.size < b.size;
}

bool sort_rows(const Row &a, const Row &b)	{
	if (a.capacity*b.area != b.capacity*a.area)
		return a.capacity*b.area > b.capacity*a.area;
	else
		return a.area < b.area;
}

void place_blocked_slots(vector<vector<int>>& field, Row &row, int row_index, vector<int>& slots)	{
	for (int i = 0; i < slots.size(); i++)
	{
		field[row_index][slots[i]] = 1;
		row.area--;
	}
}

void assign_server_to_row(Server &s, int row_index)	{
	
}

void placeServers(Input &input) {
	sort(input.servers.begin(),input.servers.end(),sort_servers);	
	vector<vector<int>> field;
	Row rows[16];
	
	for (int i = 0; i < input.r; i++)
	{
		rows[i].num = i;
		rows[i].area = input.s;
		//place_blocked_slots(i,input.blocked_slots[i]);
	}
	
	// iterate through all servers
	for (int i = 0; i < input.m; i++)
	{
		sort(rows,rows+input.r,sort_rows);
	
		// try to assign each server to worst possible row
		/*for (int j = 0; j < input.r; j++)
		{
			if (assign_server_to_row(input.servers[i],j))
			{
				rows[j].area -= input.servers[i].size;
				rows[j].capacity += input.servers[i].capacity;
			}
		}*/
	}
}
