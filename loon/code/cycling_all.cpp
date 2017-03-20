#pragma once

#include "cycling.cpp"
#include "pathfinding.cpp"

void cycling_all(Input& input, int cyclelength) {

	for(Balloon& balloon: input.balloons) {
		int t = balloon.r.size()-1;
		vector<int> tail_rs, tail_cs, tail_as, cycle_rs, cycle_cs, cycle_as;
		bool found = cyclefrom(input, balloon.r[t], balloon.c[t], balloon.h[t], cyclelength, tail_rs, tail_cs, tail_as, cycle_rs, cycle_cs, cycle_as);
		//use cycle
		if(found) {
			for(int i = 0; i < tail_rs.size(); i++) {
				balloon.r.push_back(tail_rs[i]);
				balloon.c.push_back(tail_cs[i]);
				balloon.h.push_back(tail_as[i]);
			}
			while(balloon.r.size() < input.t + 1) {
				for(int i = 0; i < cycle_rs.size(); i++) {
					balloon.r.push_back(cycle_rs[i]);
					balloon.c.push_back(cycle_cs[i]);
					balloon.h.push_back(cycle_as[i]);
				}
			}
		}
		//try to stay close to the cluster greedily
		else {
			pathfinding(input, balloon.id, input.clusters[balloon.cluster_id].center_r, input.clusters[balloon.cluster_id].center_c, -1);
		}
	}
}
