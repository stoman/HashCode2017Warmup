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

void solveSimpleHorizontal(Input& input, Output& output) {
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

void solveSimpleVertical(Input& input, Output& output) {
	for (int j = 0; j < input.c; j++)
	{
		for (int i = 0; i < input.r; i += input.h)
		{
			Slice s;
			s.r1 = i;
			s.c1 = j;
			s.r2 = min(i+input.h-1, input.r-1);
			s.c2 = j;
			output.slices.push_back(s);
		}
	}
}



int add_slice(const vector<bool> &a, int l, int r)	{
	int cnt1 = 0, cnt2 = 0;
	for (int i = l; i <= r; i++)
		if (a[i])
			cnt1++;
		else
			cnt2++;
	
	if (cnt1 >= l && cnt2 >= l)
		return r-l+1;
	return 0;
}

void solve_row(const vector<bool> &a, int row_num, int n, int l, int h, vector<Slice> &ans)	{
	vector<int> d(n,0), prev(n,0);
	
	for (int i = 0; i < n; i++)
		for (int j = 2*l; j <= h; j++)
			 if (i-j+1 >= 0)
			 {
			 	int temp = add_slice(a,i-j+1,i);
			 	if (d[i] < d[i-j+1] + temp)
				{
			 		d[i] = d[i-j+1] + temp;
					prev[i] = i-j+1;
			 	}
			}
		
	int i_max = 0;
	for (int i = 0; i < n; i++)
		if (d[i] > d[i_max])
			i_max = i;
	
	Slice c;		
	c.r1 = c.r2 = row_num;
	
	for (int i = i_max; i > 0; i--)
	{
		c.c1 = prev[i]; c.c2 = i;
		i = prev[i]-1;
		ans.push_back(c);
	}
}


void solveDP(Input& input, Output& output) {
	
	for (int i = 0; i < input.r; i++)
		solve_row(input.tomatoes[i],i,input.c,input.l,input.h,output.slices);
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
	string algorithm = "simple";
	if(argc > 2) {
		algorithm = argv[1];
	}
	
	//solve problem
	Output output;
	if(algorithm == "simple") {
		solveSimpleHorizontal(input, output);
	}
	else if(algorithm == "dp") {
		solveDP(input, output);
	}
	else {
		cerr << "unknown algorithm " << algorithm << endl;
		return 1;
	}
	
	//print output
	cout << output.slices.size() << endl;
	for(Slice slice: output.slices) {
		cout << slice.r1 << ' ' << slice.c1 << ' ' << slice.r2 << ' ' << slice.c2 << endl;
	}
};
