#include <functional>
#include <iostream>
#include <vector>
using namespace std;

class TreeAnc {
  vector<vector<int>> st;
  vector<int> start;
  vector<int> finish;
  int log;

public:
  explicit TreeAnc(const int n, const vector<int> &p, const vector<int> &s, const vector<int> &f) {
    start = s;
    finish = f;
    log = 0;
    while (1 << log <= n) {
      log++;
    }
    st.assign(n, vector<int>(log + 1));
    for (int i = 0; i < n; i++) {
      st[i][0] = p[i];
    }
    for (int j = 1; j <= log; j++) {
      for (int i = 0; i < n; i++) {
        const int anc = st[i][j - 1];
        st[i][j] = anc == -1 ? -1 : st[anc][j - 1];
      }
    }
  }

  bool anc(const int x, const int y) {
    return (start[x] <= start[y]) and (finish[y] <= finish[x]);
  }

  int lca(int x, const int y) {
    if (anc(x, y)) return x;
    if (anc(y, x)) return y;
    for (int j = log; j >= 0; j--) {
      if (st[x][j] != -1 and not anc(st[x][j], y)) {
        x = st[x][j];
      }
    }
    return st[x][0];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  vector<int> p(n), depth(n), start(n), finish(n);
  int s = 0, f = 0;
  function<void(int, int)> dfs = [&](const int x, const int par) {
    p[x] = par;
    start[x] = s;
    s++;
    for (const int &y : g[x]) {
      if (y == par) continue;
      depth[y] = depth[x] + 1;
      dfs(y, x);
    }
    finish[x] = f;
    f++;
  };
  dfs(0, -1);
  TreeAnc t(n, p, start, finish);
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << depth[x - 1] + depth[y - 1] - 2 * depth[t.lca(x - 1, y - 1)] << "\n";
  }
}