#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    g[x - 1].push_back({w, y - 1});
  }
  vector<int64> dist(n, 1e15);
  dist[0] = 0;
  set<pair<int64, int>> q;
  q.insert({0, 0});
  while (not q.empty()) {
    const int x = q.begin()->second;
    q.erase(q.begin());
    for (const pair<int, int> nbr : g[x]) {
      const int w = nbr.first;
      const int y = nbr.second;
      if (dist[y] > dist[x] + w) {
        q.erase({dist[y], y});
        dist[y] = dist[x] + w;
        q.insert({dist[y], y});
      }
    }
  }
  for (const int64 d : dist) {
    cout << d << " ";
  }
}