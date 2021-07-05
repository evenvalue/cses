#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define int64 int64_t
#define debug(x) cerr << #x << ": " << x << '\n'

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

pair<vector<int64>, vector<int>> dijkstra(const vector<vector<pair<int, int>>> &g, const int s) {
  const int n = g.size();
  vector<int64> d(n, kInfL);
  vector<int> p(n, -1);
  d[s] = 0;
  set<pair<int64, int>> q;
  q.insert({0, s});
  while (not q.empty()) {
    const int x = q.begin()->second;
    q.erase(q.begin());
    for (const auto [y, w] : g[x]) {
      if (d[y] < d[x] + w) continue;
      q.erase({d[y], y});
      d[y] = d[x] + w;
      q.insert({d[y], y});
      p[y] = x;
    }
  }
  return make_pair(d, p);
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n), gr(n);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    x--, y--;
    g[x].push_back({y, w});
    gr[y].push_back({x, w});
  }
  const vector<int64> ds = dijkstra(g, 0).first;
  const vector<int64> dt = dijkstra(gr, n - 1).first;
  int64 ans = kInfL;
  for (int x = 0; x < n; x++) {
    for (const auto [y, w] : g[x]) {
      ans = min(ans, ds[x] + (w / 2) + dt[y]);
    }
  }
  cout << ans;
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