#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
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

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  auto sets = [&](const int mask) -> int64 {
    int64 diff = 0;
    for (int bit = 0; bit < n; bit++) {
      diff += (mask & (1 << bit) ? a[bit] : -a[bit]);
    }
    return abs(diff);
  };
  int64 ans = kInfL;
  for (int mask = 0; mask < (1 << n); mask++) {
    ans = min(ans, sets(mask));
  }
  cout << ans << '\n';
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