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


bool checkSlice(Input &input, Slice &s)
{
	int t = 0;
	int f = 0;
	for (int j = s.c1; j <= s.c2; j++)
	{
		if (input.tomatoes[s.r1][j])
			t++;
		else
			f++;
	}
	
	return (t >= input.l && f >= input.l);
}


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
			if (checkSlice(input, s))
				output.slices.push_back(s);
		}
	}
}


int add_slice(const vector<bool> &a, int l, int r, int cnt_min, int h)	{
	int cnt1 = 0, cnt2 = 0;
	for (int i = l; i <= r; i++)
		if (a[i])
			cnt1++;
		else
			cnt2++;

	if (cnt1 >= cnt_min && cnt2 >= cnt_min && r-l+1 <= h)
		return r-l+1;
	return 0;
}

bool check_slice(const vector<bool> &a, int l, int r, int cnt_min, int h)	{
	int cnt1 = 0, cnt2 = 0;
	for (int i = l; i <= r; i++)
		if (a[i])
			cnt1++;
		else
			cnt2++;

	return (cnt1 >= cnt_min && cnt2 >= cnt_min && r-l+1 <= h);		
}

void solve_row(const vector<bool> &a, int row_num, int n, int l, int h, vector<Slice> &ans)	{
	vector<int> d(n,0), prev(n,0);
	
	//cerr << row_num << endl;
	
	for (int i = 0; i < n; i++)
		for (int j = max(0,i-40); j < i; j++)
		{
			int temp = add_slice(a,j,i,l,h);
			int prev_res = (j >= 0 ? d[j-1] : 0); 
			if (d[i] < prev_res + temp)
			{
					d[i] = prev_res + temp;
					prev[i] = j;
			}
		}
		
		
	/*if (row_num == 14)
	{	
		for (int i = 0; i < 60; i++)
			cerr << i << ' ' << d[i] << ' ' << prev[i] << endl;;
		cerr << endl;	
	}*/	
	
	int i_max = 0;
	for (int i = 0; i < n; i++)
		if (d[i] > d[i_max])
			i_max = i;
	
	Slice c;		
	c.r1 = c.r2 = row_num;
	
	for (int i = i_max; i > 0;)
	{	
		c.c1 = prev[i]; c.c2 = i;
		i = prev[i]-1;
		
		if (check_slice(a,c.c1,c.c2,l,h))
			ans.push_back(c);
	}
}


void solveDP(Input& input, Output& output) {
	
	for (int i = 0; i < input.r; i++)
		solve_row(input.tomatoes[i],i,input.c,input.l,input.h,output.slices);
}

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
