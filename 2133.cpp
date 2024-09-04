#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

template<typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

template<typename T1, typename T2>
pair<T1, T2> read_pair() {
  pair<T1, T2> p;
  cin >> p.first;
  cin >> p.second;
  return p;
}

template<typename T>
vector<T> read_vec(const int n, const int index = 0) {
  vector<T> v(n + index);
  for (int i = index; i < n + index; i++) {
    v[i] = read<T>();
  }
  return v;
}

template<typename T>
vector<vector<T>> read_vec_vec(const int n, const int m, const int index_n = 0, const int index_m = 0) {
  vector<vector<T>> grid(n + index_n);
  for (int i = index_n; i < n + index_n; i++) {
    grid[i] = read_vec<T>(m, index_m);
  }
  return grid;
}

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

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

struct edge {
  int x;
  int y;
  int l;
  int r;
};

class SegTree {
  const int n;
  vector<vector<array<int, 3>>> edges;

  dsu d;

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

  void calculate(const int x, const int l, const int r, vector<int> &ans) {
    for (auto &[a, b, c] : edges[x]) {
      c = d.unite(a, b);
    }
    if (l == r) {
      ans.push_back(d.comp);
    } else {
      const int mid = (l + r) / 2;
      const int y = 2 * (mid - l + 1) + x;
      calculate(x + 1, l, mid, ans);
      calculate(y, mid + 1, r, ans);
    }
    for (int i = edges[x].size() - 1; i >= 0; i--) {
      d.rollback(edges[x][i][2]);
    }
  }

public:
  SegTree(const int n, const int nodes) : n(n), edges(2 * n - 1), d(nodes) {}

  void add_edge(const int x, const int y, const int l, const int r) {
    add_edge(0, 0, n - 1, l, r, x, y);
  }

  vector<int> calculate() {
    vector<int> ans;
    calculate(0, 0, n - 1, ans);
    return ans;
  }
};

inline void solution() {
  const int n = read<int>();
  const int m = read<int>();
  const int k = read<int>();

  vector<edge> edges;

  map<pair<int, int>, int> mp;
  for (int i = 0; i < m; i++) {
    const int x = read<int>() - 1;
    const int y = read<int>() - 1;
    edges.push_back({x, y, 0});
    mp[{x, y}] = mp[{y, x}] = edges.size() - 1;
    edges.back().l = 0;
    edges.back().r = k + 1;
  }

  for (int i = 1; i <= k; i++) {
    const int t = read<int>();
    const int x = read<int>() - 1;
    const int y = read<int>() - 1;
    if (t == 1) {
      edges.push_back({x, y, i});
      mp[{x, y}] = mp[{y, x}] = edges.size() - 1;
      edges.back().l = i;
      edges.back().r = k + 1;
    } else {
      edges[mp[{x, y}]].r = i - 1;
    }
  }

  const int kTime = k + 1;

  SegTree st(kTime, n);
  for (const auto &[x, y, l, r] : edges) {
    st.add_edge(x, y, l, r);
  }

  const auto ans = st.calculate();
  for (int i = 0; i <= k; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}