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
  int n;
  cin >> n;
  vector<int> ans(n);
  if (n == 2 or n == 3) {
    cout << "NO SOLUTION";
    return;
  }
  iota(ans.begin(), ans.end(), 1);
  sort(ans.begin(), ans.end(), [](const int x, const int y) {
    return ((x & 1) != (y & 1) ? (x & 1) < (y & 1) : x < y);
  });
  for (const int x : ans) {
    cout << x << ' ';
  }
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