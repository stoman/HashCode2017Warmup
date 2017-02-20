#ifndef utils
#define utils

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//util classes
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

//transpose functions
void transpose_input(Input &input)	{

	int temp_tomatoes[1010][1010];
	
	for (int i = 0; i < input.r; i++)
	{
		for (int j = 0; j < input.c; j++)
			temp_tomatoes[j][i] = input.tomatoes[i][j];
		input.tomatoes[i].clear();
	}
	input.tomatoes.resize(input.c);
	swap(input.r, input.c);
	for (int i = 0; i < input.r; i++)
		for (int j = 0; j < input.c; j++)
			input.tomatoes[i].push_back(temp_tomatoes[i][j]);
}

void transpose_output(Output &output)	{
	for (int i = 0; i < output.slices.size(); i++)
	{
		swap(output.slices[i].r1,output.slices[i].c1);
		swap(output.slices[i].r2,output.slices[i].c2);	
	}
}

#endif
