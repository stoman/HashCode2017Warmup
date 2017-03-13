#pragma once

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "../code/util.cpp"

using namespace std;

//grade one single test case
int gradeFile(ifstream& in, ifstream& ans) {
  //read input
  Input input;
  readInput(input, in);
  
  //read answer
  ll score = 0;

  set<pair<ll, ll>> done;
  // collid, amount
  map<int, int> amount;

  ll pics;
  ans >> pics;
  for (int i = 0; i < pics; i++) {
    ll lat, lon, t, s;
    ans >> lat >> lon >> t >> s;

    // TODO: check if photo can be made by satelite s
    if (std::find(done.begin(), done.end(), make_pair(lat, lon)) == done.end()) {
      for (int c : input.objects[make_pair(lat, lon)].collections) {
        Collection& coll = input.collections[c];

        // TODO: check if t is in one of the intervals of coll
        bool inside = false;
        for (pair<ll,ll>& interval : coll.time_ranges) {
          if (t > interval.first && t < interval.second) {
            inside = true;
            break;
          }
        }

        if (inside) {
          amount[c] += 1;
          if (amount[c] == coll.objects.size()) {
            score += coll.v;
          }
          cerr << "Image at " << lat << ", " << lon << " fits into collection " << c << endl;
        }
      }
      done.insert(make_pair(lat, lon));
    }
  }
  return score;
}