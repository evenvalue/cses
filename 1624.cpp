#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#define int64 int64_t
#define debug(x) cerr << #x << ": " << x << '\n'

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

void solve() {
  vector<string> board(8);
  for (string &row : board) {
    cin >> row;
  }
  vector<bool> col(8, false), diag1(15, false), diag2(15, false);
  function<int(int)> find_ways = [&](const int r) {
    if (r == 8) return 1;
    int ways = 0;
    for (int c = 0; c < 8; c++) {
      if (board[r][c] == '*') continue;
      if (col[c] or diag1[r + c] or diag2[r - c + 7]) continue;
      col[c] = diag1[r + c] = diag2[r - c + 7] = true;
      ways += find_ways(r + 1);
      col[c] = diag1[r + c] = diag2[r - c + 7] = false;
    }
    return ways;
  };
  cout << find_ways(0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
    cout << '\n';
  }
}