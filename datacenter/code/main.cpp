#include "util.cpp"
#include "mockplaceservers.cpp"
#include "placeservers.cpp"
#include "poolservers.cpp"

//input/output code
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	
	//read input
	Input input;
	readInput(input, cin);

	//read command line args
	string algorithm = "full";
	if(argc > 1) {
		algorithm = argv[1];
	}
		
	//solve problem
	if(algorithm == "full-1") {
		placeServers(input);
		poolServers(input, input.r - 1);
	}
	else if(algorithm == "full-1-2") {
		placeServers(input);
		poolServers(input, input.r / 2);
	}
	else if(algorithm == "full-2-3") {
		placeServers(input);
		poolServers(input, input.r * 2 / 3);
	}
	else if(algorithm == "full-3-4") {
		placeServers(input);
		poolServers(input, input.r * 3 / 4);
	}
	else if(algorithm == "mockplacement") {
		mockPlaceServers(input);
		poolServers(input, input.r * 2 / 3);
	}
	else {
		cerr << "unknown algorithm" << endl;
		return 1;
	}
	
	//print output
	sort(input.servers.begin(), input.servers.end(), compareById);
	for(Server server: input.servers) {
		if(server.row == -1) {
			cout << 'x' << endl;
		}
		else {
			cout << server.row << ' ' << server.slot << ' ' << server.pool << endl;
		}
	}
};
