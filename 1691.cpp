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

  int operator[](const int x) {
    return e[x];
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  dsu comp(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    g[x].push_back({y, i});
    g[y].push_back({x, i});
    comp.unite(x, y);
  }
  int disjoint = (comp[0] < 0);
  for (int x = 1; x < n; x++) {
    disjoint += (comp[x] < 0 and comp[x] != -1);
  }
  bool impossible = (disjoint != 1);
  for (int x = 0; x < n; x++) {
    impossible |= (g[x].size() & 1);
  }
  if (impossible) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  vector<int> stack = {0};
  vector<int> order;
  vector<bool> visit(m, false);
  while (not stack.empty()) {
    const int x = stack.back();
    while (not g[x].empty()) {
      const auto [y, i] = g[x].back();
      if (visit[i]) g[x].pop_back();
      else {
        visit[i] = true;
        stack.push_back(y);
        break;
      }
    }
    if (g[x].empty()) {
      order.push_back(x);
      stack.pop_back();
    }
  }
  for (const int x : order) {
    cout << x + 1 << " ";
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}