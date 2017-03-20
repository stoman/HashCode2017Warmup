#pragma once
#include "util.cpp"

#include <set>
#include <tuple>
#include <deque>

long id(int r, int c, int a) {
    return r + 10000 * c + 1000000 * a;
}

long idl(int r, int c, int a, int l) {
    return r + 10000 * c + 1000000 * a + 100000000 * l;
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

void consider(Input& input, int r, int c, int a, int l, int rn, int cn, int an, queue<int>& q_r, queue<int>& q_c, queue<int>& q_a, queue<int>& q_l, map<long,int>& prevr, map<long,int>& prevc, map<long,int>& preva) {
    if (inbounds(rn, cn, input)) {
        q_r.push(rn);
        q_c.push(cn);
        q_a.push(an);
        q_l.push(l - 1);
        long i2 = idl(rn, cn, an, l - 1);
        prevr[i2] = r;
        prevc[i2] = c;
        preva[i2] = a;
    }
}

bool cyclefrom(Input& input, int r, int c, int a, int maxlen, deque<int>& tail_rs, deque<int>& tail_cs, deque<int>& tail_as, deque<int>& cycle_rs, deque<int>& cycle_cs, deque<int>& cycle_as) {

    cerr << "Considering " << r << " " << c << " " << a << endl;

    queue<int> q_r, q_c, q_a, q_l;

    q_r.push(r);
    q_c.push(c);
    q_a.push(a);
    q_l.push(maxlen);

    set<long> seen;
    map<long, int> prevr, prevc, preva;

    while(!q_r.empty()) {

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
            // cerr << "seen: ";
            // for (int s : seen) {
            //     cerr << s << " ";
            // }
            // cerr << endl;
        } else {
            cerr << "cycle of len " << (maxlen - l) << endl;
            cerr << "cycle to " << "(" << r << "," << c << "," << a << ")" << endl;
            // Compute cycle
            long lid = idl(r, c, a, l);
            
            int prer = prevr[lid];
            int prec = prevc[lid];
            int prea = preva[lid];
            l++;
            lid = idl(prer, prec, prea, l);
            long newid = id(prer, prec, prea);
            cerr << "going via " << "(" << prer << "," << prec << "," << prea << ")" << endl;

            cycle_rs.push_front(prer);
            cycle_rs.push_front(prec);
            cycle_rs.push_front(prea);

            // find cycle
            while(newid != i) {
                prer = prevr[lid];
                prec = prevc[lid];
                prea = preva[lid];
                l++;
                lid = idl(prer, prec, prea, l);
                newid = id(prer, prec, prea);
                cerr << "going via " << "(" << prer << "," << prec << "," << prea << ")" << endl;

                cycle_rs.push_front(prer);
                cycle_rs.push_front(prec);
                cycle_rs.push_front(prea);

                if (l >= maxlen + 2) {
                    cerr << "obviously broken. stopping" << endl;
                    return false;
                }
            }

            // find tail
            cerr << "starting tail" << endl;
            while(l < maxlen - 1) {
                prer = prevr[lid];
                prec = prevc[lid];
                prea = preva[lid];
                l++;
                lid = idl(prer, prec, prea, l);
                newid = id(prer, prec, prea);
                cerr << "going via " << "(" << prer << "," << prec << "," << prea << ")" << endl;

                tail_rs.push_front(prer);
                tail_rs.push_front(prec);
                tail_rs.push_front(prea);
            }

            return true;
        }

        if (l <= 0) {
            continue;
        }

        // reachable:
        if (a > 1) {
            int rn = tr_r(r, c, a - 1, input);
            int cn = tr_c(r, c, a - 1, input);
            int an = a - 1;
            consider(input, r, c, a, l, rn, cn, an, q_r, q_c, q_a, q_l, prevr, prevc, preva);
        }
        if (a < input.a) {
            int rn = tr_r(r, c, a + 1, input);
            int cn = tr_c(r, c, a + 1, input);
            int an = a + 1;
            consider(input, r, c, a, l, rn, cn, an, q_r, q_c, q_a, q_l, prevr, prevc, preva);
        }
        int rn = tr_r(r, c, a, input);
        int cn = tr_c(r, c, a, input);
        consider(input, r, c, a, l, rn, cn, a, q_r, q_c, q_a, q_l, prevr, prevc, preva);
    }

    return false;
}

void cycling(Input& input) {
	//TODO fill me
    cerr << "start emi" << endl;

    int len = 15;

    // graph

    for (auto& c : input.clusters) {
        deque<int> tr, tc, ta, rs, cs, as;
        cyclefrom(input, c.center_r, c.center_c, 1, 15, tr, tc, ta, rs, cs, as);
    }
    cerr << "end Emi" << endl;

}
