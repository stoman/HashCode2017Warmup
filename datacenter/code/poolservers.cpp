#include "util.cpp"
#include <limits>
#include <algorithm>
#include <utility>

int getWorstPool(Input &input, vector<int> &totalPoolCap, vector<vector<int>> &rowPoolSize)
{
	int wp = -1;
	int wp_val = numeric_limits<int>::max();
	for (int pool = 0; pool < input.p; pool++)
	{
		int garantiert = numeric_limits<int>::max();
		for (int row = 0; row < input.r; row++)
		{
			// compute remaining pool capacity
			int rem = totalPoolCap[pool] - rowPoolSize[row][pool];
			if (rem < garantiert)
			{
				garantiert = rem;
			}
		}
		if (garantiert < wp_val)
		{
			wp = pool;
			wp_val = garantiert;
		}
	}
	return wp;
}


void findMinRows(Input &input, vector<vector<int>> &rowPoolSize, int pool, vector<int> &minRows)
{
	vector<pair<int, int>> minCapRow;
	for (int row = 0; row < input.r; row++)
		minCapRow.push_back(make_pair(rowPoolSize[row][pool], row));
	sort(minCapRow.begin(), minCapRow.end());
	for (int row = 0; row < minCapRow.size(); row++)
		minRows.push_back(minCapRow[row].second);
}


int getFreeServerIdx(vector<Server> &servers, int row)
{
	int maxCap = -1;
	int maxServerIdx = -1;
	for (int i = 0; i < servers.size(); i++)
	{
		Server &s = servers[i];
		if ((s.row == row) && (s.pool == -1) && (s.capacity > maxCap))
		{
			maxCap = s.capacity;
			maxServerIdx = i;
		}
	}
	return maxServerIdx;
}


void poolServers(Input& input) 
{
	vector<int> totalPoolCap(input.p, 0);
	vector<vector<int>> rowPoolCap(input.r, vector<int>(input.p, 0));

	while (true)
	{
		bool serverAddedToPool = false;
		// pool single server
		// locate worst pool
		int wp = getWorstPool(input, totalPoolCap, rowPoolCap);

		vector<int> minRows;
		findMinRows(input, rowPoolCap, wp, minRows);

		for (int mr : minRows)
		{
			int freeServerIdx = getFreeServerIdx(input.servers, mr);
			if (freeServerIdx != -1)
			{	
				Server &fs = input.servers[freeServerIdx];
				fs.pool = wp;
				totalPoolCap[wp] += fs.capacity;
				rowPoolCap[mr][wp] += fs.capacity;
				serverAddedToPool = true;
				break;
			}
		}
		if (!serverAddedToPool)
			break;
	}
}