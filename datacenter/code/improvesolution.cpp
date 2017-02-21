#include "util.cpp"

vector<int> computeGuarantuees(Input& input) {
  vector<vector<int>> capacities(input.p, vector<int>(input.r, 0));
  for(Server& server: input.servers) {
    if(server.row != -1) {
      capacities[server.pool][server.row] += server.capacity;
    }
  }
  vector<int> guaranteed(input.p);
  for(int i = 0; i < input.p; i++) {
    int maxc = 0, sum = 0;
    for(int cap: capacities[i]) {
      maxc = max(maxc, cap);
      sum += cap;
    }
    guaranteed[i] = sum - maxc;
  }
  return guaranteed;
}

void improveSolutionOneTime(Input &input) {
  //compute capacities
  vector<int> guaranteed = computeGuarantuees(input);


  //find best, worst pool
  int wp = 0, bp = 0;
  for(int i = 1; i < input.p; i++) {
    if(guaranteed[i] > guaranteed[bp]) {
      bp = i;
    }
    if(guaranteed[i] < guaranteed[wp]) {
      wp = i;
    }
  }
  int score = guaranteed[wp];

  //find best server
  /*int best = -1;
  for(int i = 0; i < input.m; i++) {
    if(input.servers[i].pool == bp) {
      if(best == -1 || input.servers[best].capacity < input.servers[i].capacity) {
        best = i;
      }
    }
  }*/
  int best;
  do {
    best = rand() % input.m;
  } while(input.servers[best].pool != bp);

  //find some bad server
  int worst;
  do {
    worst = rand() % input.m;
  } while(input.servers[worst].pool != wp);

  //swap
  input.servers[worst].pool = bp;
  input.servers[best].pool = wp;

  //compute capacities again
  vector<int> guaranteedNew = computeGuarantuees(input);
  int scoreNew = guaranteedNew[0];
  for(int t: guaranteedNew) {
    scoreNew = min(scoreNew, t);
  }

  //swap back if this was bad
  if(scoreNew < score) {
    input.servers[worst].pool = wp;
    input.servers[best].pool = bp;
  }
}

void improveSolution(Input &input) {
  for(int i = 0; i < 500000; i++) {
    improveSolutionOneTime(input);
  }
}
