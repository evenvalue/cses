#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

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
  vector<edge> edges(m);
  for (edge &e : edges) {
    cin >> e.x >> e.y >> e.w;
    e.x--;
    e.y--;
    e.w = -e.w;
  }
  const int64 inf = 1e15;
  vector<int64> dist(n, inf);
  dist[0] = 0;
  for (int i = 0; i < n - 1; i++) {
    for (const edge &e : edges) {
      if (dist[e.x] == inf) continue;
      dist[e.y] = min(dist[e.y], dist[e.x] + e.w);
    }
  }
  for (int i = 0; i < n - 1; i++) {
    for (const edge &e : edges) {
      if (dist[e.x] == inf) continue;
      if (dist[e.x] + e.w < dist[e.y]) {
        dist[e.y] = -inf;
      }
    }
  }
  cout << (dist[n - 1] == -inf ? -1 : -dist[n - 1]) << "\n";
}