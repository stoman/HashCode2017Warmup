#pragma once
#include "util.cpp"

ll dist(Cluster& cluster, int cell_r, int cell_c) {
	return ((ll) (cluster.center_r - cell_r)) * ((ll) (cluster.center_r - cell_r)) + ((ll) (cluster.center_c - cell_c)) * ((ll) (cluster.center_c - cell_c));
}

void reassign_cells(Input& input) {
	for(Cluster& cluster: input.clusters) {
		cluster.cells.clear();
	}
	for(int i = 0; i < input.l; i++) {
		Cluster* best = &input.clusters[0];
		for(Cluster& cluster: input.clusters) {
			if(dist(*best, input.cell_r[i], input.cell_c[i]) > dist(cluster, input.cell_r[i], input.cell_c[i])) {
				best = &cluster;
			}
		}
		best->cells.push_back(make_pair(input.cell_r[i], input.cell_c[i]));
	}
}

void recompute_centers(Input& input) {
	for(Cluster& cluster: input.clusters) {
		cluster.center_r = .0;
		cluster.center_c = .0;
		for(pair<int, int>& cell: cluster.cells) {
			cluster.center_r += 1.*cell.first/cluster.cells.size();
			cluster.center_c += 1.*cell.second/cluster.cells.size();
		}
		if(cluster.center_c == .0) {
			int r = rand() % input.l;
			cluster.center_r = input.cell_r[r];
			cluster.center_c = input.cell_c[r];
		}
	}
}

void debug_clusters(Input& input) {
	for(Cluster& cluster: input.clusters) {
		for(pair<int, int>& cell: cluster.cells) {
			cerr << cell.second << " " << cell.first << " " << 1.*cluster.id/input.b << endl;
		}
	}
}

void cluster(Input& input) {
	cerr << "start clustering" << endl;

	int n = input.b;
	int m = 100;
	input.clusters.resize(n);

	//first bad matching
	/*for(int i = 0; i < input.l; i++) {
		if(i < n) {
			input.clusters[i].id = i;
			input.clusters[i].center_r = input.cell_r[i];
			input.clusters[i].center_c = input.cell_c[i];
		}
		input.clusters[i%n].cells.push_back(make_pair(input.cell_r[i], input.cell_c[i]));
	}*/

	for(int i = 0; i < n; i++) {
		//initial clusters
		int r = rand() % input.l;
		input.clusters[i].id = i;
		input.clusters[i].center_r = input.cell_r[r];
		input.clusters[i].center_c = input.cell_c[r];
		reassign_cells(input);
	}

	for(int i = 0; i < m; i++) {
		if(i % 10 == 0) {
			int debug = 0;
			for(Cluster& cluster: input.clusters) {
				if(!cluster.cells.empty()) {
					debug++;
				}
			}
			cerr << "kmeans step " << (i+1) << "/" << m << ", " << debug << " clusters with cells" << endl;
		}
		recompute_centers(input);
		reassign_cells(input);

	}

	//debug_clusters(input);

	cerr << "clustering finished" << endl;
}
