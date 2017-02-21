#ifndef utils
#define utils

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//util classes
struct Input {
	int r, c, l, h;
	vector<vector<int>> tomatoes;
};

struct Slice {
	int r1, c1, r2, c2;
};

struct Output {
	vector<Slice> slices;
};

//transpose functions
void transpose_input(Input &input)	{
	vector<vector<int> > ttt(input.c, vector<int>(input.r));
	for (int i = 0; i < input.r; i++)
		for (int j = 0; j < input.c; j++)
			ttt.at(j).at(i) = input.tomatoes.at(i).at(j);
	input.tomatoes = ttt;
	swap(input.r,input.c);
}

void transpose_output(Output &output)	{
	for (int i = 0; i < output.slices.size(); i++)
	{
		swap(output.slices[i].r1,output.slices[i].c1);
		swap(output.slices[i].r2,output.slices[i].c2);	
	}
}

#endif
