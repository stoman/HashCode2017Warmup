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
		int bfsdepth = 10;

		cluster(input, clustercount, clusteriterations);
		for (int b = 0; b < input.b; ++b)
		{
			input.balloons[b].cluster_id = b;
			double r = input.clusters[input.balloons[b].cluster_id].center_r;
			double c = input.clusters[input.balloons[b].cluster_id].center_c;
			pathfinding(input, b, r, c, -1, bfsdepth, input.c+1);
			cerr << "Pathfinding " << b << " done" << endl;
		}
	}
	else if(algorithm == "emi") {
		//play with those arguments to improve results
		double delta = input.v;
		int clustercount = input.b;
		int clusteriterations = 100;
		int cyclelength = 15;
		int bfsdepth = 10;

		cluster(input, clustercount, clusteriterations);
		for (int b = 0; b < input.b; ++b)
		{
			input.balloons[b].cluster_id = b;
			double r = input.clusters[input.balloons[b].cluster_id].center_r;
			double c = input.clusters[input.balloons[b].cluster_id].center_c;
			pathfinding(input, b, r, c, delta, bfsdepth, input.c+1);
			cerr << "Pathfinding " << b << " done" << endl;
		}
		cerr << "Cycling start" << endl;
		cycling_all(input, cyclelength,bfsdepth);
		cerr << "Cycling done" << endl;
	}
	else if(algorithm == "channel") {
		double delta = 10;
		int clusteriterations = 100;
		int bfsdepth = 10;
		int num_channels = input.r / 10;
		int clustercount = input.b;
		int delta_c = 5;
		int wait_time = 5;

		cluster(input, clustercount, clusteriterations);

		vector<int> channelids(input.b, 0);
		for(int i = 0; i < input.b; i++) {
			channelids[i] = (int) ((input.clusters[i].center_r) * num_channels / input.r);
		}

		for (int b = 0; b < input.b; ++b) {
			for(int i = 0; i < b/2; i++) {
				input.balloons[b].r.push_back(input.balloons[b].r[input.balloons[b].r.size() - 1]);
				input.balloons[b].c.push_back(input.balloons[b].c[input.balloons[b].c.size() - 1]);
				input.balloons[b].h.push_back(input.balloons[b].h[input.balloons[b].h.size() - 1]);
			}
			cerr << "computing balloon " << b << ":";
			while(input.balloons[b].r.size() <= input.t) {
				int best_cluster = -1;
				for(int c = 0; c < input.clusters.size(); c++) {
					if((int) ((input.clusters[c].center_r) * num_channels / input.r) == channelids[b]) {
						if(best_cluster == -1) {
							best_cluster = c;
						}
						else {
							int diff_c = (int) (input.clusters[c].center_c - input.balloons[b].c[input.balloons[b].c.size() - 1] + 2*input.c - delta_c - 1) % input.c;
							int diff_best = (int) (input.clusters[best_cluster].center_c - input.balloons[b].c[input.balloons[b].c.size() - 1] + 2*input.c - delta_c - 1) % input.c;
							if(diff_c < diff_best) {
								best_cluster = c;
							}
						}
					}
				}
				cerr << " " << input.balloons[b].c.size();
				//cerr << " balloon " << input.balloons[b].r[input.balloons[b].r.size() - 1] << " " << input.balloons[b].c[input.balloons[b].c.size() - 1];
				//cerr << " cluster " << input.clusters[best_cluster].center_r << " " << input.clusters[best_cluster].center_c;
				pathfinding(input, b, input.clusters[best_cluster].center_r, input.clusters[best_cluster].center_c, delta, bfsdepth, delta_c);
			}
			cerr << endl;
		}
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









