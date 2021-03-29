#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

struct edge {
  int x;
  int y;
  int w;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int64 inf = 1e16;

  int n, m;
  cin >> n >> m;
  vector<edge> edges(m);
  for (edge &e : edges) {
    cin >> e.x >> e.y >> e.w;
    e.x--;
    e.y--;
  }
  vector<int64> d(n, inf);
  vector<int> p(n, -1);
  d[0] = 0;
  int x;
  for (int i = 0; i < n; i++) {
    x = -1;
    for (const edge &e : edges) {
      if (d[e.x] + e.w < d[e.y]) {
        d[e.y] = d[e.x] + e.w;
        p[e.y] = e.x;
        x = e.y;
      }
    }
  }
  if (x == -1) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    x = p[x];
  }
  vector<int> cycle;
  for (int y = x; y != x or cycle.empty(); y = p[y]) {
    cycle.push_back(y);
  }
  cycle.push_back(x);
  reverse(cycle.begin(), cycle.end());
  for (const int &y : cycle) {
    cout << y + 1 << " ";
  }
}