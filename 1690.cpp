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

int popcount(int n) {
  int cnt = 0;
  while (n) {
    cnt += (n & 1);
    n >>= 1;
  }
  return cnt;
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
  }
  vector<vector<int>> ways(n, vector<int>(1 << (n + 1), -1));
  function<int(int, int)> dfs = [&](const int x, const int mask) {
    if (ways[x][mask] != -1) return ways[x][mask];
    else if (popcount(mask) == n) return (ways[x][mask] = 1);
    else if (x == (n - 1)) return (ways[x][mask] = 0);
    int way = 0;
    for (const int y : g[x]) {
      if (mask & (1 << y)) continue;
      way += dfs(y, mask | (1 << y));
      way -= (way >= kMod ? kMod : 0);
    }
    return (ways[x][mask] = way);
  };
  cout << dfs(0, 1);
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