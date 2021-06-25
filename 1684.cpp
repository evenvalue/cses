#include <iostream>
#include <vector>
using namespace std;

class SCC {
  const int n;
  const vector<vector<int>> g;
  vector<vector<int>> gr;

  void build_gr() {
    for (int x = 0; x < n; x++) {
      for (const int y : g[x]) {
        gr[y].push_back(x);
      }
    }
  }

  void build_order(const int x, vector<bool> &visit, vector<int> &order) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (visit[y]) continue;
      build_order(y, visit, order);
    }
    order.push_back(x);
  }

  void build_comp(const int x, const int c) {
    comp[x] = c;
    for (const int y : gr[x]) {
      if (comp[y] != -1) continue;
      build_comp(y, c);
    }
  }

  void kosaraju() {
    vector<int> order;
    order.reserve(n);
    vector<bool> visit(n, false);
    for (int x = 0; x < n; x++) {
      if (visit[x]) continue;
      build_order(x, visit, order);
    }
    int c = 0;
    while (not order.empty()) {
      const int x = order.back();
      order.pop_back();
      if (comp[x] != -1) continue;
      build_comp(x, c++);
    }
  }

public:
  vector<int> comp;

  explicit SCC(const vector<vector<int>> &g) : g(g), n(g.size()), gr(g.size()), comp(g.size(), -1) {
    build_gr();
    kosaraju();
  }
};

class twosat {
  vector<vector<int>> g;

public:
  vector<bool> allot;

  explicit twosat(const int n) : g(2 * n), allot(n) {}

  void add_edge(bool xsign, int x, bool ysign, int y) {
    x = (2 * abs(x)) + (not xsign);
    y = (2 * abs(y)) + (not ysign);
    g[x].push_back(y);
  }

  bool solve() {
    SCC scc(g);
    const vector<int> &comp = scc.comp;
    for (int x = 0; x < comp.size(); x += 2) {
      if (comp[x] == comp[x + 1]) return false;
      allot[x / 2] = (comp[x] > comp[x + 1]);
    }
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  twosat ts(m);
  for (int i = 0; i < n; i++) {
    char c;
    bool xsign, ysign;
    int x, y;
    cin >> c >> x;
    xsign = (c == '+');
    cin >> c >> y;
    ysign = (c == '+');
    x--, y--;
    ts.add_edge(not xsign, x, ysign, y);
    ts.add_edge(not ysign, y, xsign, x);
  }
  if (not ts.solve()) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  for (const bool top : ts.allot) {
    cout << (top ? '+' : '-') << ' ';
  }
  cout << '\n';
}