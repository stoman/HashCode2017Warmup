#pragma once
#include "util.cpp"

#include <set>
#include <tuple>

long id(int r, int c, int a) {
    return r + 10000 * c + 1000000 * a;
}

bool inbounds(int r, int c, Input& input) {
    return (0 <= r && r < input.r && 0 <= c && c < input.c);
}

int tr_r(int r, int c, int a, Input& input) {
    // cerr << "translating " << r << " " << c << " " << a << endl;
    return r + input.movement_r[r][c][a];
}
int tr_c(int r, int c, int a, Input& input) {
    // cerr << "translating " << r << " " << c << " " << a << endl;
    return (c + input.movement_c[r][c][a] + input.c) % input.c;
}

void cycling(Input& input) {
	//TODO fill me
    cerr << "start emi" << endl;

    int len = 15;

    // graph

    for (auto& c : input.clusters) {
        cerr << "Considering " << c.center_r << " " << c.center_c << endl;

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

            // cerr << "p(" << r << "," << c << "," << a << "," << l << ")" << endl;

            long i = id(r, c, a);
            if (seen.find(i) == seen.end()) {
                seen.insert(i);
            } else {
                cerr << "cycle of len " << (len - l) << endl;
            }

            if (l <= 0) {
                continue;
            }

            // cerr << "one";

            // reachable:
            if (a > 1) {
                int rn = tr_r(r, c, a - 1, input);
                int cn = tr_c(r, c, a - 1, input);
                if (inbounds(rn, cn, input)) {
                    q_r.push(rn);
                    q_c.push(cn);
                    q_a.push(a - 1);
                    q_l.push(l - 1);
                }
            }
            if (a < input.a) {
                int rn = tr_r(r, c, a + 1, input);
                int cn = tr_c(r, c, a + 1, input);
                if (inbounds(rn, cn, input)) {
                    q_r.push(rn);
                    q_c.push(cn);
                    q_a.push(a + 1);
                    q_l.push(l - 1);
                }
            }
            // cerr << "two";

            int rn = tr_r(r, c, a, input);
            int cn = tr_c(r, c, a, input);
            if (inbounds(rn, cn, input)) {
                q_r.push(rn);
                q_c.push(cn);
                q_a.push(a);
                q_l.push(l - 1);
            }
        }
    }
    cerr << "end Emi" << endl;

}