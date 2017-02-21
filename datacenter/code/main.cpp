#include "util.cpp"
#include "placeservers.cpp"
#include "poolservers.cpp"

//input/output code
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	
	//read input
	Input input;
	readInput(input, cin);

	//TODO read command line args
		
	//solve problem
	placeServers(input);
	poolServers(input);
	
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
