#include "util.cpp"
#include "dp.cpp"
#include "simple.cpp"

//input/output code
int main(int argc, char* argv[]) {
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
	
	//read command line args
	string algorithm = "simplehorizontal";
	if(argc > 1) {
		algorithm = argv[1];
	}
		
	//solve problem
	Output output;
	cerr << "using algorithm " << algorithm << endl;
	if(algorithm == "simplehorizontal") {
		solveSimple(input, output);
	}
	else if(algorithm == "simplevertical") {
		transpose_input(input);
		solveSimple(input, output);
		transpose_output(output);
	}
	else if(algorithm == "dp") {
		solveDP(input, output);
	}
	else if(algorithm == "dptranspose")	{
		transpose_input(input);
		solveDP(input,output);
		transpose_output(output);
	}
	else {
		cerr << "unknown algorithm" << endl;
		return 1;
	}

	//print output
	cout << output.slices.size() << endl;
	int area = 0;
	for(Slice slice: output.slices) {
		area += (slice.r2 - slice.r1 + 1) * (slice.c2 - slice.c1 + 1);
		cout << slice.r1 << ' ' << slice.c1 << ' ' << slice.r2 << ' ' << slice.c2 << endl;
	}
	cerr << "cells used: " << area << endl;
};
