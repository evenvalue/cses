#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef int64_t int64;

vector<vector<int64>> dijkstra(const vector<vector<pair<int, int>>> &g, int k) {
  const int64 kInf = 1e15 + 10;
  const int n = g.size();
  vector<vector<int64>> d(n, vector<int64>(k, kInf));
  multiset<pair<int64, int>> q;
  q.insert({0, 0});
  while (not q.empty()) {
    const int x = q.begin()->second;
    const int64 dist = q.begin()->first;
    q.erase(q.begin());
    for (const auto [w, y] : g[x]) {
      if (d[y][k - 1] <= dist + w) continue;
      const auto it = q.find({d[y][k - 1], y});
      if (it != q.end()) q.erase(it);
      d[y][k - 1] = dist + w;
      q.insert({d[y][k - 1], y});
      sort(d[y].begin(), d[y].end());
    }
  }
  return d;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    g[x - 1].push_back({w, y - 1});
  }
  auto d = dijkstra(g, k);
  for (const int64 &path : d[n - 1]) {
    cout << path << ' ';
  }
  cout << '\n';
}