//call this script like this to have live scores:
//while true; do git pull; make -j grades.html; sleep 15; done;
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "../code/util.cpp"

using namespace std;


int columndist(int C, int c1, int c2)
{
  return min(abs(c1-c2), C - abs(c1-c2));
}


void updateBalloonPosition(Input &input, int t, int b, 
  vector<vector<int>> &alti, vector<int> &pos_r, 
    vector<int> &pos_c, vector<int> &pos_a)
{
  // update height
  pos_a[b] += alti[t][b];

  // update position
  if (pos_a[b] != 0)
  {
    int r = pos_r[b];
    int c = pos_c[b];
    int a = pos_a[b];
    int r_new = r + input.movement_r[r][c][a];
    int c_new = (c + input.movement_c[r][c][a] + input.c) % input.c;
    pos_r[b] = r_new;
    pos_c[b] = c_new;
  }
}


//grade one single test case
int gradeFile(ifstream& in, ifstream& ans) {
  //read input
  Input input;
  readInput(input, in);
  
  //read answer
  vector<vector<int>> alti(input.t, vector<int>(input.b));
  for (int t = 0; t < input.t; ++t)
  {
    for (int b = 0; b < input.b; ++b)
    {
      ans >> alti[t][b];
      if (alti[t][b] != -1 && alti[t][b] != 0 && alti[t][b] != 1)
      {
        cerr << "ERROR: Output data has altitude change of " << alti[t][b] << endl;
        return -2;
      }
    }
  }

  set<int> activeBalloons;
  for (int i = 0; i < input.b; ++i)
  {
    activeBalloons.insert(i);
  }

  vector<int> pos_r(input.b, input.rs);
  vector<int> pos_c(input.b, input.cs);
  vector<int> pos_a(input.b, 0);

  int score = 0;
  for (int t = 0; t < input.t; ++t)
  {
    // all cells are not covered in the beginning
    set<int> unvoc_cell_ids;
    for (int i = 0; i < input.l; ++i)
    {
      unvoc_cell_ids.insert(i);
    }

    set<int> lost_balloons;
    for (int b : activeBalloons)
    {
      updateBalloonPosition(input, t, b, alti, pos_r, pos_c, pos_a);

      // check if balloon is still in correct altitude level
      if (pos_r[b] < 0 || pos_r[b] >= input.r)
      {
        cerr << "Balloon " << b << " is lost in time step " << t << endl;
        lost_balloons.insert(b);
      }

      // check if altitude is wrong
      if (pos_a[b] < 0 || pos_a[b] > input.a)
      {
        cerr << "ERROR: Balloon " << b 
          << " leaves altitude in time step " << t 
          << ". Altitude is " << pos_a[b] << endl;
        return -1;
      }

      // check if current ballooon covers new cells
      set<int> covered_cell_ids;
      for (int c_id : unvoc_cell_ids)
      {
        int u = input.cell_r[c_id];
        int v = input.cell_c[c_id];
        int coldist = columndist(input.c, pos_c[b], v);
        int ru = pos_r[b] - u;
        if (ru * ru + coldist * coldist <= input.v * input.v)
        {
          covered_cell_ids.insert(c_id);
        }
      }
      for (int cov_id : covered_cell_ids)
      {
        unvoc_cell_ids.erase(cov_id);
      }
    }
    score += input.l - unvoc_cell_ids.size();

    // delete all balloons that are out of bounds
    for (int lb : lost_balloons)
    {
      activeBalloons.erase(lb);
    }
  }

  cerr << "Score: " << score << endl;
  return score;
}

//iterate over all test cases
int main() {
  //open data directory
  DIR* datadir = opendir("data");
  if(!datadir) {
    cerr << "can't find data directory" << endl;
    return 1;
  }
  //save result data
  set<string> algorithms, testcases;
  map<pair<string, string>, int> scores;
  map<string, int> maxscores;
  //iterate over all files
  struct dirent* file;
  ifstream in, ans;
  while(0 != (file = readdir(datadir))) {
    string ansname = file->d_name;
    if(ansname.size() > 4 && !ansname.compare(ansname.size() - 4, 4, ".ans")) {
      cerr << "solving file " << ansname << endl;
      string testcase = ansname.substr(ansname.find_first_of(".") + 1, ansname.find_last_of(".") - ansname.find_first_of(".") - 1);
      testcases.insert(testcase);
      string algorithm = ansname.substr(0, ansname.find_first_of("."));
      algorithms.insert(algorithm);
      in.open("data/" + testcase + ".in");
      ans.open("data/" + ansname);
      scores[make_pair(algorithm, testcase)] = gradeFile(in, ans);
      maxscores[testcase] = max(maxscores[testcase], scores[make_pair(algorithm, testcase)]);
      in.close();
      ans.close();
    }
  }
  //print header
  cout << "<html><head><meta http-equiv=\"refresh\" content=\"15\" >"
          "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\">"
          "<link rel=\"stylesheet\" href=\"https://code.getmdl.io/1.3.0/material.indigo-pink.min.css\">"
          "<script defer src=\"https://code.getmdl.io/1.3.0/material.min.js\">"
          "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0\">"
          "</script></head><body style=\"padding: 3em\">" << endl;
  //print table
  cout << "<table class=\"mdl-data-table mdl-js-data-table mdl-shadow--2dp\" style=\"margin-left: auto; margin-right: auto;\">" << endl << "<thead><tr><th class=\"mdl-data-table__cell--non-numeric mdl-data-table__header--sorted-ascending\">algorithm</th>";
  for(string testcase: testcases) {
    cout << "<th class=\"mdl-data-table__cell--non-numeric\">" << testcase << "</th>";
  }
  cout << "<th class=\"mdl-data-table__cell--non-numeric\">sum</th></tr></thead><tbody>" << endl;
  for(string algorithm: algorithms) {
    int sum = 0;
    cout << "<tr><td class=\"mdl-data-table__cell--non-numeric\">" << algorithm << "</td>";
    for(string testcase: testcases) {
      if(scores.find(make_pair(algorithm, testcase)) != scores.end()) {
        cout << "<td" << (scores[make_pair(algorithm, testcase)] == maxscores[testcase] ? " style=\"font-weight: bold;\"" : "") << ">" << scores[make_pair(algorithm, testcase)] << "</td>";
        sum += scores[make_pair(algorithm, testcase)];
      }
      else {
        cout << "<td>-</td>";
      }
    }
    cout << "<td>" << sum << "</td></tr>" << endl;
  }
  int sum = 0;
  cout << "<tr><td class=\"mdl-data-table__cell--non-numeric\">maximum</td>";
  for(string testcase: testcases) {
    cout << "<td>" << maxscores[testcase] << "</td>";
    sum += maxscores[testcase];
  }
  cout << "<td style=\"font-weight: bold;\">" << sum << "</td></tr>" << endl << "</tbody></table>" << endl;
  //print footer
  cout << "</body></html>" << endl;
}
