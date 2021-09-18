#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

ifstream fin("input.txt");
ofstream fout("output.txt");

void solve(const int TestCase) {
  int n, q;
  cin >> n >> q;
  const int lg = 31;
  int st[n][lg];
  for (int i = 0; i < n; i++) {
    cin >> st[i][0];
    st[i][0]--;
  }
  for (int jump = 1; jump < lg; jump++) {
    for (int i = 0; i < n; i++) {
      st[i][jump] = st[st[i][jump - 1]][jump - 1];
    }
  }
  while (q--) {
    int x, k;
    cin >> x >> k;
    x--;
    for (int j = lg; j >= 0; j--) {
      if (const int cur_jump = (1 << j); k & cur_jump) {
        k -= cur_jump;
        x = st[x][j];
      }
    }
    cout << x + 1 << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  auto begin = std::chrono::high_resolution_clock::now();

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solve(tc);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}