#include <functional>
#include <iostream>
#include <vector>
using namespace std;

class TreeAnc {
  vector<vector<int>> st;
  const vector<int> start;
  const vector<int> finish;
  int log;

public:
  explicit TreeAnc(const int n, const vector<int> &p, const vector<int> &s, const vector<int> &f) : start(s), finish(f) {
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

  bool anc(const int x, const int y) const {
    return (start[x] <= start[y]) and (finish[y] <= finish[x]);
  }

  int lca(int x, const int y) const {
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

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  vector<int> p(n), start(n), finish(n);
  int s = 0, f = 0;
  function<void(int)> dfs1 = [&](const int x) {
    start[x] = s++;
    for (int &y : g[x]) {
      if (y == p[x]) continue;
      p[y] = x;
      dfs1(y);
    }
    finish[x] = f++;
  };
  p[0] = -1;
  dfs1(0);
  TreeAnc t(n, p, start, finish);
  vector<int> pref(n);
  while (m--) {
    int x, y;
    cin >> x >> y;
    pref[x - 1]++;
    pref[y - 1]++;
    const int lca = t.lca(x - 1, y - 1);
    pref[lca]--;
    if (p[lca] != -1) pref[p[lca]]--;
  }
  function<void(int)> dfs2 = [&](const int x) {
    for (const int &y : g[x]) {
      if (y == p[x]) continue;
      dfs2(y);
      pref[x] += pref[y];
    }
  };
  dfs2(0);
  for (int i = 0; i < n; i++) {
    cout << pref[i] << " ";
  }
}