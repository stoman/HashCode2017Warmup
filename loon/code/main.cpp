#include "util.cpp"
#include "cluster.cpp"
#include "pathfinding.cpp"
#include "cycling.cpp"

//input/output code
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	srand(time(NULL));

	//read input
	Input input;
	readInput(input, cin);

	//read command line args
	string algorithm = "";
	if(argc > 1) {
		algorithm = argv[1];
	}
		
	//solve problem
	cerr << "using algorithm " << algorithm << endl;
	if(algorithm == "naive") {
		cluster(input);
		for (int b = 0; b < input.b; ++b)
		{
			double r = input.clusters[b].center_r;
			double c = input.clusters[b].center_c;
			pathfinding(input, b, r, c, -1);
		}
	}
	else if(algorithm == "emi") {
		cluster(input);
		for (int b = 0; b < input.b; ++b)
		{
			double r = input.clusters[b].center_r;
			double c = input.clusters[b].center_c;
			pathfinding(input, b, r, c, -1);
		}
		cycling(input);
	}
	else {
		cerr << "unknown algorithm" << endl;
		return 1;
	}
	
	// Output
	// first time step
	/*for (int b = 0; b < input.b; ++b)
	{
		cout << input.balloons[b].h[0] << " ";
	}
	cout << endl;*/

	// all other steps
	for (int t = 1; t <= input.t; ++t)
	{
		for (int b = 0; b < input.b; ++b)
		{
			int diff = 0;
			if (input.balloons[b].h.size() >= t)
				diff = input.balloons[b].h[t] - input.balloons[b].h[t-1];
			cout << diff << " ";
		}
		cout << endl;
	}
};









