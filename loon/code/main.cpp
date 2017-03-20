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

		//kirill

	}
	else if(algorithm == "emi") {
		cluster(input);

		// kirill

		cycling(input);
	}
	else {
		cerr << "unknown algorithm" << endl;
		return 1;
	}
	
	//print output
	//TODO print output
};
