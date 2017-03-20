#pragma once
#include "util.cpp"

void cluster(Input& input) {
	int n = input.b;
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