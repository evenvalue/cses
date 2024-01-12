#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
  #define debug(...) print(#__VA_ARGS__, __VA_ARGS__)
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace Read {
int Int() {
  int x;
  cin >> x;
  return x;
}
int64 Int64() {
  int64 x;
  cin >> x;
  return x;
}
char Char() {
  char c;
  cin >> c;
  return c;
}
string String() {
  string s;
  cin >> s;
  return s;
}
double Double() {
  return stod(String());
}
ld LongDouble() {
  return stold(String());
}
template<typename T1, typename T2>
pair<T1, T2> Pair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
vector<vector<T>> VecVec(const int n, const int m) {
  vector<vector<T>> v(n);
  for (vector<T> &vec : v) {
    vec = Vec<T>(m);
  }
  return v;
}
}// namespace Read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

template<class node, class F = std::function<node(const node &, const node &)>>
class SegTree {
  int n = 0;
  std::vector<node> t;
  F unite;

  void build(const int x, const int l, const int r, const std::vector<node> &a) {
    if (l == r) {
      t[x] = a[l];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  void update(const int x, const int l, const int r, const int p, const node &v) {
    if (l == p and p == r) {
      t[x] = v;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      update(x + 1, l, mid, p, v);
    } else {
      update(y, mid + 1, r, p, v);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  node query(const int x, const int l, const int r, const int ql, const int qr) const {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr), query(y, mid + 1, r, ql, qr));
    }
  }

public:
  SegTree() = default;
  explicit SegTree(const int n, const node e, F f) : n(n), t(2 * n - 1, e), unite(std::move(f)) {}
  explicit SegTree(const std::vector<node> &a, F f) : n(a.size()), t(2 * (a.size()) - 1), unite(std::move(f)) {
    build(0, 0, n - 1, a);
  }

  void update(const int p, const node &v) {
    assert(0 <= p and p < n);
    update(0, 0, n - 1, p, v);
  }

  [[nodiscard]] node query(const int l, const int r) const {
    assert(0 <= l and l <= r and r < n);
    return query(0, 0, n - 1, l, r);
  }
};

class HeavyLight {
  const int n;
  const vector<vector<int>> g;

  vector<int> parent;
  vector<int> heavy;
  vector<int> depth;
  vector<int> pos;
  vector<int> root;

  int dfs(const int x, const int p) {
    int cur_size = 1;
    int max_size = 0;
    for (const int y : g[x]) {
      if (y == p) continue;

      depth[y] = depth[x] + 1;
      parent[y] = x;

      const int child_size = dfs(y, x);
      if (child_size > max_size) {
        heavy[x] = y;
        max_size = child_size;
      }

      cur_size += child_size;
    }

    return cur_size;
  }

public:
  explicit HeavyLight(const vector<vector<int>> &t)
      : n(t.size()), g(t),
        parent(n, -1), heavy(n, -1), depth(n),
        pos(n), root(n) {

    dfs(0, -1);

    for (int x = 0, i = 0; x < n; x++) {
      if (parent[x] == -1 or heavy[parent[x]] != x) {
        for (int y = x; y != -1; y = heavy[y]) {
          root[y] = x;
          pos[y] = i++;
        }
      }
    }
  }

  template<class F = function<void(int, int)>>
  int operate(int x, int y, const F &op) {
    while (root[x] != root[y]) {
      if (depth[root[x]] > depth[root[y]]) swap(x, y);
      op(pos[root[y]], pos[y]);
      y = parent[root[y]];
    }
    if (depth[x] > depth[y]) swap(x, y);
    op(pos[x], pos[y]);
    return x;
  }
};

inline void solution() {
  const int n = Read::Int();
  const int q = Read::Int();

  vector<int> a = Read::Vec<int>(n);
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    const int x = Read::Int() - 1;
    const int y = Read::Int() - 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  HeavyLight hld(g);

  SegTree<int> st(n, 0, [&](const int x, const int y) {
    return max(x, y);
  });

  auto maxima = [&](const int x, const int y) {
    int ans = -1;
    hld.operate(x, y, [&](const int l, const int r) {
      ans = max(ans, st.query(l, r));
    });
    return ans;
  };

  auto fix = [&](const int x, const int value) {
    hld.operate(x, x, [&](const int l, const int r) {
      assert(l == r);
      st.update(l, value);
    });
  };

  for (int x = 0; x < n; x++) {
    fix(x, a[x]);
  }

  for (int i = 0; i < q; i++) {
    const int t = Read::Int();
    if (t == 1) {
      const int x = Read::Int() - 1;
      const int v = Read::Int();
      fix(x, v);
    } else {
      const int x = Read::Int() - 1;
      const int y = Read::Int() - 1;
      cout << maxima(x, y) << ' ';
    }
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
