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

namespace read {
int Int() {
  int x;
  cin >> x;
  return x;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;

class LazySegTree {
  struct node {
    int64 sum = 0;
    int64 times = 0;
    int64 minus = 0;
  };

  const int n;
  vector<node> t;

  int64 till(const int64 n) {
    return (n * (n + 1)) / 2;
  }

  int64 range(const int l, const int r) {
    return till(r) - till(l - 1);
  }

  static node unite(const node l, const node r) {
    node ans;
    ans.sum = l.sum + r.sum;
    return ans;
  }

  void push(const int x, const int l, const int r) {
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;

    auto &[_, times, minus] = t[x];

    t[x + 1].sum += times * range(l, mid) - ((mid - l + 1) * minus);
    t[x + 1].times += times;
    t[x + 1].minus += minus;

    t[y].sum += times * range(mid + 1, r) - ((r - mid) * minus);
    t[y].times += times;
    t[y].minus += minus;

    times = 0;
    minus = 0;
  }

  void build(const int x, const int l, const int r, const vector<int64> &a) {
    if (l == r) {
      t[x].sum = a[l];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  void update(const int x, const int l, const int r, const int ql, const int qr, const int first) {
    if (ql <= l and r <= qr) {
      t[x].sum += range(l, r) - (r - l + 1) * 1LL * first;
      t[x].times++;
      t[x].minus += first;
      return;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      update(x + 1, l, mid, ql, qr, first);
    }
    if (mid < qr) {
      update(y, mid + 1, r, ql, qr, first);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  node query(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    push(x, l, r);
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
  explicit LazySegTree(const vector<int64> &a) : n(a.size()), t(2 * n - 1) {
    build(0, 0, n - 1, a);
  }

  void update(const int l, const int r) {
    update(0, 0, n - 1, l, r, l - 1);
  }

  int64 query(const int l, const int r) {
    return query(0, 0, n - 1, l, r).sum;
  }
};

inline void solution() {
  const int n = read::Int();
  const int q = read::Int();

  vector<int64> a = read::Vec<int64>(n);

  LazySegTree st(a);
  for (int query = 0; query < q; query++) {
    const int type = read::Int();
    const int l = read::Int() - 1;
    const int r = read::Int() - 1;
    if (type == 1) {
      st.update(l, r);
    } else {
      cout << st.query(l, r) << '\n';
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}