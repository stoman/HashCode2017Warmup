#include "util.cpp"

int add_slice(const vector<char> &a, int l, int r, int cnt_min, int h)	{
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

bool check_slice(const vector<char> &a, int l, int r, int cnt_min, int h)	{
	int cnt1 = 0, cnt2 = 0;
	for (int i = l; i <= r; i++)
		if (a[i])
			cnt1++;
		else
			cnt2++;

	return (cnt1 >= cnt_min && cnt2 >= cnt_min && r-l+1 <= h);		
}

void solve_row(const vector<char> &a, int row_num, int n, int l, int h, vector<Slice> &ans)	{
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