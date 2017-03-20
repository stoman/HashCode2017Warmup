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
		Cluster& best = input.clusters[0];
		for(Cluster& cluster: input.clusters) {
			if(dist(best, input.cell_r[i], input.cell_c[i]) > dist(cluster, input.cell_r[i], input.cell_c[i])) {
				cluster = best;
			}
		}
		best.cells.push_back(make_pair(input.cell_r[i], input.cell_c[i]));
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
	}
	reassign_cells(input);
}

void cluster(Input& input) {
	int n = input.b;

	//first bad matching
	input.clusters.resize(n);
	for(int i = 0; i < input.l; i++) {
		if(i < n) {
			input.clusters[i].id = i;
			input.clusters[i].center_r = input.cell_r[i];
			input.clusters[i].center_c = input.cell_c[i];
		}
		input.clusters[i%n].cells.push_back(make_pair(input.cell_r[i], input.cell_c[i]));
	}
}
