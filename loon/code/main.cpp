#include "util.cpp"
#include "cluster.cpp"
#include "pathfinding.cpp"
#include "cycling.cpp"
#include "cycling_all.cpp"

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
		//play with those arguments to improve results
		int clustercount = input.b;
		int clusteriterations = 100;
		int bfsdepth = 9;

		cluster(input, clustercount, clusteriterations);
		for (int b = 0; b < input.b; ++b)
		{
			input.balloons[b].cluster_id = b;
			double r = input.clusters[input.balloons[b].cluster_id].center_r;
			double c = input.clusters[input.balloons[b].cluster_id].center_c;
			pathfinding(input, b, r, c, -1, bfsdepth);
			cerr << "Pathfinding " << b << " done" << endl;
		}
	}
	else if(algorithm == "emi") {
		//play with those arguments to improve results
		double delta = input.v;
		int clustercount = input.b;
		int clusteriterations = 100;
		int cyclelength = 15;
		int bfsdepth = 9;

		cluster(input, clustercount, clusteriterations);
		for (int b = 0; b < input.b; ++b)
		{
			input.balloons[b].cluster_id = b;
			double r = input.clusters[input.balloons[b].cluster_id].center_r;
			double c = input.clusters[input.balloons[b].cluster_id].center_c;
			pathfinding(input, b, r, c, delta,bfsdepth);
			cerr << "Pathfinding " << b << " done" << endl;
		}
		cerr << "Cycling start" << endl;
		cycling_all(input, cyclelength,bfsdepth);
		cerr << "Cycling done" << endl;
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









