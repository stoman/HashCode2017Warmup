#include <iostream>
#include <vector>

using namespace std;

struct Input {
	int r, c, l, h;
	vector<vector<bool>> tomatoes;
};

struct Slice {
	int r1, c1, r2, c2;
};

struct Output {
	vector<Slice> slices;
};

void solveSimple(Input& input, Output& output) {
	for (int i = 0; i < input.r; i++)
	{
		for (int j = 0; j < input.c; j += input.h)
		{
			Slice s;
			s.r1 = i;
			s.c1 = j;
			s.r2 = i;
			s.c2 = min(j+input.h-1, input.c-1);
			output.slices.push_back(s);
		}
	}
}

void solveDP(Input& input, Output& output) {
	//TODO add code here
}

int main() {
	ios::sync_with_stdio(false);
	
	//read input
	Input input;
	cin >> input.r >> input.c >> input.l >> input.h;
	for(int i = 0; i < input.r; i++) {
		vector<bool> row(input.c);
		for(int j = 0; j < input.c; j++) {
			char cell;
			cin >> cell;
			row[j] = cell == 'T';
		}
		input.tomatoes.push_back(row);
		//TODO do we read line breaks?
	}
	
	//solve problem
	Output output;
	solve(input, output);
	
	//print output
	cout << output.slices.size() << endl;
	
};
