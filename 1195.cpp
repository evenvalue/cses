#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define int64 int64_t

const int64 inf = 1e15;

void dijkstra(const vector<vector<pair<int, int>>> &g, const int s, vector<int64> &d) {
  const int n = g.size();
  d.assign(n, inf);
  d[s] = 0;
  set<pair<int64, int>> q;
  q.insert({0, s});
  while (not q.empty()) {
    const int x = q.begin()->second;
    q.erase(q.begin());
    for (const pair<int, int> nbr : g[x]) {
      const int y = nbr.second;
      const int w = nbr.first;
      if (d[x] + w < d[y]) {
        q.erase({d[y], y});
        d[y] = d[x] + w;
        q.insert({d[y], y});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  struct edge {
    int x;
    int y;
    int w;
  };

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n), gr(n);
  vector<edge> edges(m);
  for (edge &e : edges) {
    cin >> e.x >> e.y >> e.w;
    e.x--;
    e.y--;
    g[e.x].push_back({e.w, e.y});
    gr[e.y].push_back({e.w, e.x});
  }
  vector<int64> ds, dt;
  dijkstra(g, 0, ds);
  dijkstra(gr, n - 1, dt);
  int64 ans = inf;
  for (const edge &e : edges) {
    if (ds[e.x] == inf or dt[e.y] == inf) continue;
    ans = min(ans, ds[e.x] + dt[e.y] + (e.w / 2));
  }
  cout << ans << "\n";
}