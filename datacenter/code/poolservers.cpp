#include "util.cpp"
#include <limits>
#include <algorithm>
#include <utility>

void getWorstPools(Input &input, vector<int> &totalPoolCap, vector<vector<int>> &rowPoolSize, vector<int> &worstPoolIds)
{
	vector<int> minPoolCap(input.p, numeric_limits<int>::max());
	//vector<int> minPoolCapRow(input.p, -1);

	for (int row = 0; row < input.r; row++)
	{
		// this 'row' fails
		for (int pool = 0; pool < input.p; pool++)
		{
			// compute remaining pool capacity
			int rem = totalPoolCap[pool] - rowPoolSize[row][pool];
			if (rem < minPoolCap[pool])
			{
				minPoolCap[pool] = rem;
				//minPoolCapRow[pool] = row;
			}
		}
	}

	// find the worst pool
	vector<pair<int,int>> worstPools;
	for (int pool = 0; pool < input.p; pool++)
		worstPools.push_back(make_pair(minPoolCap[pool], pool));
	sort(worstPools.begin(), worstPools.end());
	for (int pool = 0; pool < input.p; pool++)
		worstPoolsId.push_back(worstPools[i].second);
}



void findMinRows(vector<vector<int>> &rowPoolSize, int pool, vector<int> &minRows)
{
	vector<pair<int, int>> minCapRow;
	for (int row = 0; row < input.r; row++)
		minCapRow.push_back(make_pair(rowPoolSize[row][worstPool], row));
	sort(minCapRow.begin(), minCapRow.end());
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
	vector<vector<int>> rowPoolSize(input.r, vector<int>(input.p, 0));

	while (true)
	{
		bool serverAddedToPool = false;
		// pool single server
		// locate worst pool
		vector<int> worstPoolIds;
		getWorstPools(input, totalPoolCap, rowPoolSize, worstPoolIds);

		for (int wp : worstPoolIds)
		{
			vector<int> minRows;
			findMinRows(rowPoolSize, wp, minRows);

			for (int mr : minRows)
			{
				int freeServerIdx = getFreeServerIdx(servers, mr);
				if (freeServerIdx != -1)
				{	
					Server &fs = servers[freeServerIdx];
					fs.pool = wp;
					totalPoolCap[wp] += fs.capacity;
					rowPoolSize[mr][wp] += fs.capacity;
					serverAddedToPool = true;
					break;
				}
			}
			if (serverAddedToPool)
				break;
		}
		if (!serverAddedToPool)
			break;
	}
}