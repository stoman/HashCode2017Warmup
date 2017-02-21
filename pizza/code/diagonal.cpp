#include "util.cpp"
#include <algorithm>

//helper function to sort larger slices up
bool compareSlices(const pair<int, int>& lhs, const std::pair<int, int>& rhs) {
 return lhs.first * lhs.second > rhs.first * rhs.second;
 //prefer squares (this makes the results slightly worse)
 //return lhs.first * lhs.second - abs(lhs.first - lhs.second) > rhs.first * rhs.second - abs(rhs.first - rhs.second);
};

//compute possible slices
vector<pair<int, int>> possibleSlices(Input& input) {
	//find all possible slices
	vector<pair<int, int>> r;
	for(int i = 1; i <= min(input.r, input.h); i++) {
		for(int j = 1; j <= min(input.c, input.h); j++) {
			if(2 * input.l <= i * j && i * j <= input.h) {
				r.push_back(make_pair(i, j));
			}
		}
	}
	//sort the larger ones up
	sort(r.begin(), r.end(), compareSlices);
	return r;
}

void solveDiagonal(Input& input, Output& output) {
	vector<pair<int, int>> slices = possibleSlices(input);
	vector<vector<bool>> used(input.r, vector<bool>(input.c, false));
	//iterate over field using diagonals
	for(int s = 0; s < input.r + input.c - 2; s++) {
		for(int x = 0; x <= min(input.r - 1, s); x++) {
			int y = s - x;
			//try to place a slice here
			if(!used[x][y]) {
				bool placed = false;
				for(pair<int, int> slice: slices) {
					if(!placed && x + slice.first <= input.r && y + slice.second <= input.c) {
						//check whether this slice is ok
						//this can be done much more efficiently, but the input is small...
						bool ok = true;
						vector<int> ingredients(2, 0);
						for(int tx = x; tx < x + slice.first; tx++) {
							for(int ty = y; ty < y + slice.second; ty++) {
								ok &= !used[tx][ty];
								ingredients[input.tomatoes[tx][ty]]++;
							}
						}
						if(ok && ingredients[0] >= input.l && ingredients[1] >= input.l) {
							//cut slice
							for(int tx = x; tx < x + slice.first; tx++) {
								for(int ty = y; ty < y + slice.second; ty++) {
									used[tx][ty] = true;
								}
							}
							Slice newslice;
							newslice.r1 = x;
							newslice.c1 = y;
							newslice.r2 = x + slice.first - 1;
							newslice.c2 = y + slice.second - 1;
							output.slices.push_back(newslice);
							placed = true;
						}
					}
				}
			}
		}		
	}
}