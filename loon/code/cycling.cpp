#pragma once
#include "util.cpp"

#include <set>
#include <tuple>

long id(int r, int c, int h) {
    return r + 1000 * c + 100000 * h;
}

int tr_r(int r, int c, int a, Input& input) {
    return r + input.movement_r[r][c][a];
}
int tr_c(int r, int c, int a, Input& input) {
    return c + input.movement_c[r][c][a];
}

void cycling(Input& input) {
	//TODO fill me
    cerr << "start emi";

    int len = 10;

    // graph

    for (auto& c : input.clusters) {
        queue<int> q_r;
        queue<int> q_c;
        queue<int> q_a;
        queue<int> q_l;

        q_r.push(c.center_r);
        q_c.push(c.center_c);
        q_a.push(1);
        q_l.push(len);

        while(!q_r.empty()) {
            set<long> seen;

            int r = q_r.front();
            int c = q_c.front();
            int a = q_a.front();
            int l = q_l.front();
            q_r.pop();
            q_c.pop();
            q_a.pop();
            q_l.pop();

            long i = id(r, c, a);
            if (find(seen.begin(), seen.end(), i) == seen.end()) {
                seen.insert(i);
            } else {
                cout << "cycle of len " << (len - l);
            }

            if (len <= 0) {
                continue;
            }

            // reachable:
            if (a > 1) {
                q_r.push(tr_r(r, c, a - 1, input));
                q_c.push(tr_c(r, c, a - 1, input));
                q_a.push(a - 1);
                q_l.push(l - 1);
            }
            if (a < input.a - 1) {
                q_r.push(tr_r(r, c, a + 1, input));
                q_c.push(tr_c(r, c, a + 1, input));
                q_a.push(a + 1);
                q_l.push(l - 1);
            }
            q_r.push(tr_r(r, c, a, input));
            q_c.push(tr_c(r, c, a, input));
            q_a.push(a);
            q_l.push(l - 1);
        }
    }

}