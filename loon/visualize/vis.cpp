#include "../code/util.cpp"
#include <iostream>
#include <fstream>
#include <set>

//input/output code
int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    srand(time(NULL));

    //read input
    Input input;
    readInput(input, cin);

    //read command line args
    char* ansfile = argv[1];
    ifstream ans;
    ans.open(ansfile);

    // for (int i = 0; i < input.b; i++) {
    //     input.balloons[i].r[0] = input.rs;
    //     input.balloons[i].c[0] = input.cs;
    //     input.balloons[i].h[0] = 0;
    // }

    set<int> losts;

    for (int tt = 0; tt < input.t; tt++) {
        // cerr << "time " << tt << endl;
        for (int i = 0; i < input.b; i++) {
            if (losts.find(i) != losts.end()) {
                continue;
            }

            int da;
            ans >> da;

            int rc = input.balloons[i].r[tt];
            int cc = input.balloons[i].c[tt];
            int ac = input.balloons[i].h[tt];
            int an = ac + da;

            if (rc < 0 || input.r <= rc || an < 0 || an > input.a) {
                cerr << "loon " << i << " lost at " << rc << " " << cc << " " << an << endl;
                losts.insert(i);
                continue;
            }

            int rn = rc;
            int cn = cc ;
            if (an != 0) {
                rn += input.movement_r[rc][cc][an];
                cn += input.movement_c[rc][cc][an];
            }

            cout << cc << ' ' << rc << ' ' << cn-cc << ' ' << rn-rc << ' ' << an << endl;
            cn = (cn + input.c) % input.c;

            if (tt + 1 < input.t) {
                input.balloons[i].r.push_back(rn);
                input.balloons[i].c.push_back(cn);
                input.balloons[i].h.push_back(an);
            }
        }
    }
    // cerr << "done" << endl;
    ans.close();
    return 0;
};
