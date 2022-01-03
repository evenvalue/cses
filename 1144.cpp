#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

using int64 = int64_t;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

[[maybe_unused]] int readInt() {
  int x;
  cin >> x;
  return x;
}
[[maybe_unused]] int64 readInt64() {
  int64 x;
  cin >> x;
  return x;
}
[[maybe_unused]] char readChar() {
  char c;
  cin >> c;
  return c;
}
[[maybe_unused]] string readString() {
  string s;
  cin >> s;
  return s;
}
[[maybe_unused]] double readDouble() {
  return stod(readString());
}
[[maybe_unused]] ld readLongDouble() {
  return stold(readString());
}
template<typename T1, typename T2>
[[maybe_unused]] pair<T1, T2> readPair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
[[maybe_unused]] vector<T> readVec(const int sz) {
  vector<T> v(sz);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
[[maybe_unused]] vector<vector<T>> readVecVec(const int n, const int m) {
  vector<vector<T>> a(n);
  for (vector<T> &v : a) {
    v = readVec<T>(m);
  }
  return a;
}

const int64 kInf64 = 2e18 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

namespace cp {
template<class node, class F = std::function<node(const node &, const node &)>>
class SegTree {
  int n = 0;
  std::vector<node> t;
  const F unite;

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

  [[nodiscard]] node query(const int x, const int l, const int r, const int ql, const int qr) const {
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

  void set(const int p, const node &v) {
    assert(0 <= p and p < n);
    update(0, 0, n - 1, p, v);
  }

  node get(const int l, const int r) {
    assert(0 <= l and l <= r and r < n);
    return query(0, 0, n - 1, l, r);
  }
};

class Compress {
  bool sorted = false;
  vector<int> v;

public:
  void add(const int x) {
    v.push_back(x);
    sorted = false;
  }

  int size() {
    return (int) v.size();
  }

  int get_index(const int x) {
    if (not sorted) sort(v.begin(), v.end());
    sorted = true;
    return (int) distance(v.begin(), lower_bound(v.begin(), v.end(), x));
  }
};
} //namespace cp


struct query {
  bool upd;
  int x, y;
};

void solution() {
  const int n = readInt(), q = readInt();
  vector<int> a = readVec<int>(n);

  cp::Compress c;

  for (const int x : a) c.add(x);

  vector<query> queries(q);
  for (auto &[u, x, y] : queries) {
    u = (readChar() == '!');
    x = readInt(), y = readInt();
    if (u) {
      x--;
    } else {
      c.add(x);
    }
    c.add(y);
  }

  const int mx = c.size();
  cp::SegTree<int> st(mx, 0, [](const int l, const int r) {
    return l + r;
  });

  for (int i = 0; i < n; i++) {
    a[i] = c.get_index(a[i]);
    st.set(a[i], st.get(a[i], a[i]) + 1);
  }

  for (const auto &[u, x, y] : queries) {
    if (u) {
      st.set(a[x], st.get(a[x], a[x]) - 1);
      a[x] = c.get_index(y);
      st.set(a[x], st.get(a[x], a[x]) + 1);
    } else {
      cout << st.get(c.get_index(x), c.get_index(y)) << '\n';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const auto begin = std::chrono::high_resolution_clock::now();

  //  freopen(".in", "r", stdin);
  //  freopen(".out", "w", stdout);

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solution();
  }

  const auto end = std::chrono::high_resolution_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}