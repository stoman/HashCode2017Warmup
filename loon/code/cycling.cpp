#pragma once
#include "util.cpp"

#include <set>
#include <tuple>
#include <deque>
#include <stack>

long id(int r, int c, int a) {
    return r + 10000 * c + 1000000 * a;
}

bool inbounds(int r, int c, int a, Input& input) {
    return (0 <= r && r < input.r && 0 <= c && c < input.c && 0 < a && a <= input.a);
}

int tr_r(int r, int c, int a, Input& input) {
    // cerr << "translating " << r << " " << c << " " << a << endl;
    return r + input.movement_r[r][c][a];
}
int tr_c(int r, int c, int a, Input& input) {
    // cerr << "translating " << r << " " << c << " " << a << endl;
    return (c + input.movement_c[r][c][a] + input.c) % input.c;
}

// bool consider(Input& input, int r, int c, int a, int l, int rn, int cn, int an, vector<int>& q_r, vector<int>& q_c, vector<int>& q_a, vector<int>& q_l, map<long,int>& prevr, map<long,int>& prevc, map<long,int>& preva, set<long>& seen) {
//     cerr << "Considering " << rn << " " << cn << " " << an << endl;

//     long i = id(rn, cn, an);
//     long iold = id(r, c, a);
//     if (inbounds(rn, cn, input) && seen.find(i) == seen.end()) {
//         seen.insert(i);

//         q_r.push_back(r);
//         q_c.push_back(c);
//         q_a.push_back(a);
//         q_l.push_back(l);

//         q_r.push_back(rn);
//         q_c.push_back(cn);
//         q_a.push_back(an);
//         q_l.push_back(l - 1);
//         long i2 = idl(rn, cn, an, l - 1);
//         prevr[i2] = r;
//         prevc[i2] = c;
//         preva[i2] = a;
//         return true;
//     }
//     return false;
// }

void buildcycle(int r, int c, int a, int rn, int cn, int an, int l, int maxlen, map<long, int>& prevr, map<long, int>& prevc, map<long, int>& preva, deque<int>& tail_rs, deque<int>& tail_cs, deque<int>& tail_as, deque<int>& cycle_rs, deque<int>& cycle_cs, deque<int>& cycle_as) {
    cerr << "cycle to " << "(" << rn << "," << cn << "," << an << ")" << endl;
    // Compute cycle
    long i = id(rn, cn, an);

    cycle_rs.clear();
    cycle_cs.clear();
    cycle_as.clear();
    tail_rs.clear();
    tail_cs.clear();
    tail_as.clear();
    
    int prer = r;
    int prec = c;
    int prea = a;
    // l++;

    long newid = id(prer, prec, prea);

    // find cycle
    while(newid != i) {
        cerr << "going via " << "(" << prer << "," << prec << "," << prea << "," << l << ")" << endl;
        cycle_rs.push_front(prer);
        cycle_cs.push_front(prec);
        cycle_as.push_front(prea);

        prer = prevr[newid];
        prec = prevc[newid];
        prea = preva[newid];
        newid = id(prer, prec, prea);
        l++;

        if (l > maxlen + 5) {
            cerr << "obviously broken. stopping" << endl;
            return;
        }
    }

    // find tail
    cerr << "starting tail" << endl;
    while(l < maxlen) {
        prer = prevr[newid];
        prec = prevc[newid];
        prea = preva[newid];
        l++;
        newid = id(prer, prec, prea);
        cerr << "going via " << "(" << prer << "," << prec << "," << prea << "," << l << ")" << endl;

        tail_rs.push_front(prer);
        tail_cs.push_front(prec);
        tail_as.push_front(prea);
    }

    // remove first step - (starting node)
    if (tail_rs.empty()) {
        cycle_rs.push_back(rn);
        cycle_cs.push_back(cn);
        cycle_as.push_back(an);
    } else {
        tail_rs.pop_front();
        tail_cs.pop_front();
        tail_as.pop_front();
    }

    cerr << "tail: ";
    for (int j = 0; j < tail_rs.size(); j++) {
        cerr << "(" << tail_rs[j] << "," << tail_cs[j] << "," << tail_as[j] << "), ";
    }
    cerr << "cycle: ";
    for (int j = 0; j < cycle_rs.size(); j++) {
        cerr << "(" << cycle_rs[j] << "," << cycle_cs[j] << "," << cycle_as[j] << "), ";
    }
    cerr << endl;
}

bool dfsvisit(int r, int c, int a, int l, int maxlen, map<long, int>& prevr, map<long, int>& prevc, map<long, int>& preva, map<long,int>& state, int& tt, map<long, int>& disc, map<long, int> finish, Input& input, deque<int>& tail_rs, deque<int>& tail_cs, deque<int>& tail_as, deque<int>& cycle_rs, deque<int>& cycle_cs, deque<int>& cycle_as) {
    long i = id(r, c, a);
    // cerr << "visiting " << r << " " << c << " " << a << endl;

    state[i] = 1; // grey
    tt++;

    disc[i] = tt;

    if (l > 0) {
        vector<int> dirs({-1, 0, 1});
        for (auto& d : dirs) {
            int an = a + d;
            int rn = tr_r(r, c, an, input);
            int cn = tr_c(r, c, an, input);

            if (inbounds(rn, cn, an, input)) {
                long i2 = id(rn, cn, an);

                if (state[i2] == 0) {
                    // white
                    prevr[i2] = r;
                    prevc[i2] = c;
                    preva[i2] = a;

                    if (dfsvisit(rn, cn, an, l - 1, maxlen, prevr, prevc, preva, state, tt, disc, finish, input,tail_rs, tail_cs, tail_as, cycle_rs, cycle_cs, cycle_as)) {
                        return true;
                    }
                } else if (state[i2] == 1) {
                    // grey
                    cerr << "Found cycle" << endl;
                    buildcycle(r, c, a, rn, cn, an, l, maxlen, prevr, prevc, preva, tail_rs, tail_cs, tail_as, cycle_rs, cycle_cs, cycle_as);
                    return true;
                }
            }
        }
    }

    state[i] = 2; // black
    tt++;
    finish[i] = tt;
    // no cycle yet
    return false;
}

bool cyclefrom(Input& input, int r, int c, int a, int maxlen, deque<int>& tail_rs, deque<int>& tail_cs, deque<int>& tail_as, deque<int>& cycle_rs, deque<int>& cycle_cs, deque<int>& cycle_as) {
    cerr << "Cycling from " << r << " " << c << " " << a << endl;

    if (!inbounds(r, c, a, input)) {
        cerr << "Coordinates given not in bounds. Returning false";
        return false;
    }
    
    map<long, int> prevr, prevc, preva, state, disc, finish;

    int tt = 0;

    return dfsvisit(r, c, a, maxlen, maxlen, prevr, prevc, preva, state, tt, disc, finish, input, tail_rs, tail_cs, tail_as, cycle_rs, cycle_cs, cycle_as);
}

// bool cyclefrom(Input& input, int r, int c, int a, int maxlen, deque<int>& tail_rs, deque<int>& tail_cs, deque<int>& tail_as, deque<int>& cycle_rs, deque<int>& cycle_cs, deque<int>& cycle_as) {


//     vector<int> q_r, q_c, q_a, q_l;

//     q_r.push_back(r);
//     q_c.push_back(c);
//     q_a.push_back(a);
//     q_l.push_back(maxlen);

//     set<long> seen;
//     map<long, int> prevr, prevc, preva;

//     while(!q_r.empty()) {

//         int r = q_r.back();
//         int c = q_c.back();
//         int a = q_a.back();
//         int l = q_l.back();
//         q_r.pop_back();
//         q_c.pop_back();
//         q_a.pop_back();
//         q_l.pop_back();

//         long i = id(r, c, a);

//         cerr << "p(" << r << "," << c << "," << a << "," << l << ")" << endl;

//         // is still in stack?
//         bool instack = false;
//         for (int j = 0; j < q_r.size(); j++) {
//             if (q_r[j] == r && q_c[j] == c && q_a[j] == a) {
//                 instack = true;
//                 break;
//             }
//         }
//         if (instack) {
//             cerr << "cycle of len " << (maxlen - l) << endl;
//             cerr << "cycle to " << "(" << r << "," << c << "," << a << ")" << endl;
//             // Compute cycle
//             long lid = idl(r, c, a, l);
            
//             int prer = prevr[lid];
//             int prec = prevc[lid];
//             int prea = preva[lid];
//             l++;
//             lid = idl(prer, prec, prea, l);
//             long newid = id(prer, prec, prea);
//             cerr << "going via " << "(" << prer << "," << prec << "," << prea << ")" << endl;

//             cycle_rs.push_front(prer);
//             cycle_rs.push_front(prec);
//             cycle_rs.push_front(prea);

//             // find cycle
//             while(newid != i) {
//                 prer = prevr[lid];
//                 prec = prevc[lid];
//                 prea = preva[lid];
//                 l++;
//                 lid = idl(prer, prec, prea, l);
//                 newid = id(prer, prec, prea);
//                 cerr << "going via " << "(" << prer << "," << prec << "," << prea << ")" << endl;

//                 cycle_rs.push_front(prer);
//                 cycle_rs.push_front(prec);
//                 cycle_rs.push_front(prea);

//                 if (l >= maxlen + 2) {
//                     cerr << "obviously broken. stopping" << endl;
//                     return false;
//                 }
//             }

//             // find tail
//             cerr << "starting tail" << endl;
//             while(l < maxlen - 1) {
//                 prer = prevr[lid];
//                 prec = prevc[lid];
//                 prea = preva[lid];
//                 l++;
//                 lid = idl(prer, prec, prea, l);
//                 newid = id(prer, prec, prea);
//                 cerr << "going via " << "(" << prer << "," << prec << "," << prea << ")" << endl;

//                 tail_rs.push_front(prer);
//                 tail_rs.push_front(prec);
//                 tail_rs.push_front(prea);
//             }
//             return true;
//         }

//         if (l > 0) {
//             // reachable:
//             // only push one node at a tt
//             bool doing = false;
//             if (a > 1) {
//                 int rn = tr_r(r, c, a - 1, input);
//                 int cn = tr_c(r, c, a - 1, input);
//                 int an = a - 1;
//                 doing = doing || consider(input, r, c, a, l, rn, cn, an, q_r, q_c, q_a, q_l, prevr, prevc, preva, seen);
//             }
//             if (a < input.a) {
//                 int rn = tr_r(r, c, a + 1, input);
//                 int cn = tr_c(r, c, a + 1, input);
//                 int an = a + 1;
//                 doing = doing || consider(input, r, c, a, l, rn, cn, an, q_r, q_c, q_a, q_l, prevr, prevc, preva, seen);
//             }
//             int rn = tr_r(r, c, a, input);
//             int cn = tr_c(r, c, a, input);
//             doing = doing || consider(input, r, c, a, l, rn, cn, a, q_r, q_c, q_a, q_l, prevr, prevc, preva, seen);
//         }
//     }

//     return false;
// }

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
