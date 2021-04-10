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
  vector<int> p(n, -1);
  for (int x = 1; x < n; x++) {
    cin >> p[x];
    p[x]--;
    g[p[x]].push_back(x);
  }
  vector<int> start(n);
  vector<int> finish(n);
  int s = 0, f = 0;
  function<void(int)> dfs = [&](const int x) {
    start[x] = s;
    s++;
    for (const int y : g[x]) {
      dfs(y);
    }
    finish[x] = f;
    f++;
  };
  dfs(0);
  TreeAnc t(n, p, start, finish);
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << t.lca(x - 1, y - 1) + 1 << "\n";
  }
}