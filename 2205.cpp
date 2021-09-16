#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
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

void print(const int n, const vector<int> &ans) {
  for (const int x : ans) {
    for (int i = n - 1; i >= 0; i--) {
      cout << (x & (1 << i) ? 1 : 0);
    }
    cout << '\n';
  }
}

void solve() {
  int n;
  cin >> n;
  vector<int> ans{0};
  ans.reserve(1 << n);
  for (int i = 0; i < n; i++) {
    for (int j = (int)ans.size() - 1; j >= 0; j--) {
      ans.push_back((1 << i) + ans[j]);
    }
  }
  print(n, ans);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
  }
}