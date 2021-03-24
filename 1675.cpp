#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class dsu {
  vector<int> e;

public:
  explicit dsu(const int n) : e(n, -1) {}

  int find(const int x) {
    return e[x] < 0 ? x : (e[x] = find(e[x]));
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return true;
  }
};

struct edge {
  int x;
  int y;
  int w;

  bool operator<(const edge &other) const {
    return w < other.w;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  dsu kruskal(n);
  vector<edge> edges(m);
  for (edge &e : edges) {
    cin >> e.x >> e.y >> e.w;
    e.x--;
    e.y--;
  }
  sort(edges.begin(), edges.end());
  int comp = n;
  long long ans = 0;
  for (const edge &e : edges) {
    if (kruskal.unite(e.x, e.y)) {
      comp--;
      ans += e.w;
    }
  }
  if (comp == 1) {
    cout << ans;
  } else {
    cout << "IMPOSSIBLE";
  }
  cout << "\n";
}