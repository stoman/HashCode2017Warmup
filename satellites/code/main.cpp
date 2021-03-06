#include "util.cpp"
#include "schedule_photos.cpp"

using namespace std;

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
		schedule_photos(input);
	}
	else {
		cerr << "unknown algorithm" << endl;
		return 1;
	}
	
	//print output
	int n = 0;
	for(Satellite& satellite: input.satellites) {
		n += satellite.photos.size();
	}
	cout << n << endl;
	for(int i = 0; i < input.satellites.size(); i++) {
		for(auto& photo: input.satellites[i].photos) {
			cout << photo.second.lat << ' ' << photo.second.lon << ' ' << photo.first << ' ' << i << endl;
		}
	}
};
