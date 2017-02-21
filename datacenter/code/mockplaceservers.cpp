#include "util.cpp"

//input handling
bool compareByEfficiency(const Server &a, const Server &b) {
  return a.capacity * b.size > b.capacity * a.size;
}


void mockPlaceServers(Input &input) {
  sort(input.servers.begin(), input.servers.end(), compareByEfficiency);
  vector<vector<bool>> slotsBlocked(input.r, vector<bool>(input.s, false));
  for(int i = 0; i < input.r; i++) {
    for(int j: input.blocked_slots[i]) {
      slotsBlocked[i][j] = true;
    }
  }
  for(int i = 0; i < input.m; i++) {
    for(int j = 0; j < input.s - input.servers[i].size; j++) {
      bool ok = true;
      for(int k = j; k < j + input.servers[i].size; k++) {
        ok &= !slotsBlocked[i % input.r][k];
      }
      if(ok) {
        //place server
        for(int k = j; k < j + input.servers[i].size; k++) {
          slotsBlocked[i % input.r][k] = true;
        }
        input.servers[i].row = i % input.r;
        input.servers[i].slot = j;
        //go to next
        j = input.s;
      }
    }
  }
}
