#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

class dsu {
  const int n;
  vector<int> e;
  vector<array<int, 3>> history;

  int time = 0;

public:
  int comp;

  dsu(const int n) : n(n), e(n, -1), comp(n) {}

  int find(const int x) {
    return (e[x] < 0 ? x : find(e[x]));
  }

  int unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return time++;
    if (e[x] > e[y]) swap(x, y);
    history.push_back({y, e[y], time});
    e[x] += e[y];
    e[y] = x;
    comp--;
    return time++;
  }

  void rollback(const int t) {
    if (history.empty()) return;
    if (history.back()[2] != t) return;
    const int y = history.back()[0];
    const int sz = history.back()[1];
    e[e[y]] -= sz;
    e[y] = sz;
    history.pop_back();
    comp++;
  }
};

class SegTree {
  const int n;
  vector<vector<array<int, 3>>> edges;

  void add_edge(const int x, const int l, const int r, const int ql, const int qr, const int a, const int b) {
    if (ql <= l and r <= qr) {
      edges[x].push_back({a, b, -1});
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      add_edge(x + 1, l, mid, ql, qr, a, b);
    }
    if (mid < qr) {
      add_edge(y, mid + 1, r, ql, qr, a, b);
    }
  }

  void calculate(const int x, const int l, const int r, dsu &d, vector<int> &ans) {
    for (auto &[a, b, c] : edges[x]) {
      c = d.unite(a, b);
    }
    if (l == r) {
      ans.push_back(d.comp);
    } else {
      const int mid = (l + r) / 2;
      const int y = 2 * (mid - l + 1) + x;
      calculate(x + 1, l, mid, d, ans);
      calculate(y, mid + 1, r, d, ans);
    }
    for (int i = edges[x].size() - 1; i >= 0; i--) {
      d.rollback(edges[x][i][2]);
    }
  }

public:
  SegTree(const int n) : n(n), edges(2 * n - 1) {}

  void add_edge(const int x, const int y, const int l, const int r) {
    add_edge(0, 0, n - 1, l, r, x, y);
  }

  vector<int> calculate(dsu &d) {
    vector<int> ans;
    calculate(0, 0, n - 1, d, ans);
    return ans;
  }
};

struct edge {
  int x;
  int y;
  int l;
  int r;
};

inline void solution() {
  const int n = read<int>();
  const int m = read<int>();
  const int k = read<int>();

  vector<edge> edges;

  map<pair<int, int>, int> idx;
  for (int i = 0; i < m; i++) {
    const int x = read<int>() - 1;
    const int y = read<int>() - 1;
    edges.push_back({x, y, 0});
    idx[{x, y}] = idx[{y, x}] = edges.size() - 1;
    edges.back().l = 0;
    edges.back().r = k + 1;
  }

  for (int i = 1; i <= k; i++) {
    const int t = read<int>();
    const int x = read<int>() - 1;
    const int y = read<int>() - 1;
    if (t == 1) {
      edges.push_back({x, y, i});
      idx[{x, y}] = idx[{y, x}] = edges.size() - 1;
      edges.back().l = i;
      edges.back().r = k + 1;
    } else {
      edges[idx[{x, y}]].r = i - 1;
    }
  }

  const int kTime = k + 1;

  SegTree st(kTime);
  for (const auto &[x, y, l, r] : edges) {
    st.add_edge(x, y, l, r);
  }

  dsu d(n);

  const auto ans = st.calculate(d);
  for (int i = 0; i <= k; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();
}