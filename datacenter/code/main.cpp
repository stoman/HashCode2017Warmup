#include "util.cpp"
#include "placeservers.cpp"
#include "poolservers.cpp"

bool compareById(const Server &a, const Server &b) {
    return a.id < b.id;
}

//input/output code
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	
	//read input
	Input input;
	cin >> input.r >> input.s >> input.u >> input.p >> input.m;
	input.blocked_slots.resize(input.r);
	for(int i = 0; i < input.u; i++) {
		int r, s;
		cin >> r >> s;
		input.blocked_slots[r].push_back(s);
	}
	for(int i = 0; i < input.m; i++) {
		int z, c;
		cin >> z >> c;
		Server server;
		server.id = i;
		server.capacity = c;
		server.size = z;
		input.servers.push_back(server);
	}

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
