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


bool cyclefrom(Input& input, int r, int c, int a, int maxlen, vector<int>& cycle_rs, vector<int>& cycle_cs, vector<int>& cycle_as) {

    cerr << "Considering " << r << " " << c << " " << a << endl;

    queue<int> q_r, q_c, q_a, q_l;

    q_r.push(r);
    q_c.push(c);
    q_a.push(a);
    q_l.push(maxlen);

    set<long> seen;

    while(!q_r.empty()) {

        int r = q_r.front();
        int c = q_c.front();
        int a = q_a.front();
        int l = q_l.front();
        q_r.pop();
        q_c.pop();
        q_a.pop();
        q_l.pop();

        map<long, int> prevr, prevc, preva;

        // cerr << "p(" << r << "," << c << "," << a << "," << l << ")" << endl;

        long i = id(r, c, a);
        if (seen.find(i) == seen.end()) {
            seen.insert(i);
            // cerr << "seen: ";
            // for (int s : seen) {
            //     cerr << s << " ";
            // }
            // cerr << endl;
        } else {
            cerr << "cycle of len " << (maxlen - l) << endl;
            // Compute cycle

            break;
        }

        if (l <= 0) {
            continue;
        }

        // cerr << "one";

        // reachable:
        if (a > 1) {
            int rn = tr_r(r, c, a - 1, input);
            int cn = tr_c(r, c, a - 1, input);
            int an = a - 1;
            if (inbounds(rn, cn, input)) {
                q_r.push(rn);
                q_c.push(cn);
                q_a.push(an);
                q_l.push(l - 1);
            }

        }
        if (a < input.a) {
            int rn = tr_r(r, c, a + 1, input);
            int cn = tr_c(r, c, a + 1, input);
            int an = a + 1;
            if (inbounds(rn, cn, input)) {
                q_r.push(rn);
                q_c.push(cn);
                q_a.push(an);
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

void cycling(Input& input) {
	//TODO fill me
    cerr << "start emi" << endl;

    int len = 15;

    // graph

    for (auto& c : input.clusters) {
        vector<int> rs, cs, as;
        cyclefrom(input, c.center_r, c.center_c, 1, 15, rs, cs, as);
    }
    cerr << "end Emi" << endl;

}
