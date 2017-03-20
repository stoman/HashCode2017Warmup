#pragma once
#include "util.cpp"

#include <map>

int id(int r, int c, int h) {
    return r + 1000 * c + 100000 * h;
}

void cycling(Input& input) {
	//TODO fill me
    cout << "start emi";

    int len = 10;

    // graph
    map<int, vector<int>> graph;

    queue<pair<int,int>> points;

    for (auto& c : input.clusters) {
        pair<int, int> p = make_pair(id(c.center_r, c.center_c, 1),len);
        points.push(p);
    }


    while(!points.empty()) {
        pair<int, int> p = points.front();

        cout << p.first;
        points.pop();
    }

}