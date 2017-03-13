#include "grader.cpp"

int main() {

    string testcase = "example";
    string algorithm = "naive";

    ifstream in, ans;
    in.open("data/" + testcase + ".in");
    ans.open("data/" + algorithm + "." + testcase + ".ans");

    cout << "Score: " << gradeFile(in, ans) << endl;

    in.close();
    ans.close();

    return 0;
}
