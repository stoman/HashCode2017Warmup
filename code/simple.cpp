#include "util.cpp"

bool checkSlice(Input &input, Slice &s)
{
	int t = 0;
	int f = 0;
	for (int j = s.c1; j <= s.c2; j++)
	{
		if (input.tomatoes.at(s.r1).at(j))
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
