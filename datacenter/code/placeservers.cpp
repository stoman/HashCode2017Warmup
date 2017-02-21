#include "util.cpp"


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
		return a.capacity*b.area < b.capacity*a.area;
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

bool assign_server_to_row(int s, vector<int>& field, Server &server)	{
	for (int i = 0; i <= s-server.size; i++)
	{	
	 	int cnt_occ = 0;
		for (int j = 0; j < server.size; j++)
			cnt_occ += field[i+j];
		if (cnt_occ == 0)
		{
			for (int j = 0; j < server.size; j++)
				field[i+j] = 1;
			server.slot = i;
			return true;
		}
	}
	return false;
}

void placeServers(Input &input) {
	// sort servers
	sort(input.servers.begin(),input.servers.end(),sort_servers);	
	
	// create field and rows
	vector<vector<int>> field(input.r, vector<int>(input.s));
	vector<Row> rows(input.r);
	
	for (int i = 0; i < input.r; i++)
	{
		rows[i].num = i;
		rows[i].capacity = 0;
		rows[i].area = input.s;
		place_blocked_slots(field,rows[i],i,input.blocked_slots[i]);
	}
	
	// iterate through all servers
	for (int i = 0; i < input.m; i++)
	{
		sort(rows.begin(),rows.end(),sort_rows);
		
		/*
		cerr << "server: " << input.servers[i].capacity << ' ' << input.servers[i].size << endl;
		for (int j = 0; j < rows.size(); j++)
			cerr << rows[j].num << ' ' << rows[j].capacity << ' ' << rows[j].area << endl;;
		cerr << endl;
		
		for (int j = 0; j < input.r; j++)
		{
			for (int l = 0; l < input.s; l++)
				cerr << field[j][l];
			cerr << endl;
		}*/
		
		// try to assign each server to worst possible row
		for (int j = 0; j < input.r; j++)
		{
			if (assign_server_to_row(input.s,field[rows[j].num],input.servers[i]))
			{
				rows[j].area -= input.servers[i].size;
				rows[j].capacity += input.servers[i].capacity;
				input.servers[i].row = rows[j].num;
				break;
			}
		}
	}
}
