#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
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
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

template<class Node>
class LazySegTree {
  using Unite_t = std::function<Node(const Node &, const Node &)>;
  using Apply_t = std::function<void(Node &, const Node &)>;
  using Unlazy = std::function<void(Node &)>;

  size_t n = 0;
  std::vector<Node> t;

  Unite_t unite;
  Apply_t apply;
  Unlazy activate;

  void push(const size_t x, const size_t l, const size_t r) {
    const size_t mid = (l + r) / 2;
    const size_t y = 2 * (mid - l + 1) + x;
    apply(t[x + 1], t[x]);
    apply(t[y], t[x]);
    activate(t[x]);
  }

  void update(const size_t x, const size_t l, const size_t r, const size_t ql, const size_t qr, const Node upd) {
    if (ql <= l and r <= qr) {
      apply(t[x], upd);
      return;
    }
    push(x, l, r);
    const size_t mid = (l + r) / 2;
    const size_t y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      update(x + 1, l, mid, ql, qr, upd);
    }
    if (mid < qr) {
      update(y, mid + 1, r, ql, qr, upd);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  Node query(const size_t x, const size_t l, const size_t r, const size_t ql, const size_t qr) {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    push(x, l, r);
    const size_t mid = (l + r) / 2;
    const size_t y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr), query(y, mid + 1, r, ql, qr));
    }
  }

  void build(const int x, const int l, const int r, const std::vector<Node> &a) {
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

public:
  LazySegTree(const size_t n, const Node e, const Unite_t unite, const Apply_t apply, const Unlazy activate)
      : n(n), t(2 * n - 1, e), unite(unite), apply(apply), activate(activate) {}

  LazySegTree(const std::vector<Node> &a, const Unite_t unite, const Apply_t apply, const Unlazy activate)
      : n(a.size()), t(2 * n - 1), unite(unite), apply(apply), activate(activate) {
    build(0, 0, n - 1, a);
  }

  void update(const int ql, const int qr, const Node upd) {
    assert(0 <= ql and ql <= qr and qr < n);
    update(0, 0, n - 1, ql, qr, upd);
  }

  Node query(const int ql, const int qr) {
    assert(0 <= ql and ql <= qr and qr < n);
    return query(0, 0, n - 1, ql, qr);
  }

  LazySegTree<Node> &operator=(LazySegTree<Node> other) {
    swap(n, other.n);
    swap(t, other.t);
    swap(unite, other.unite);
    swap(apply, other.apply);
    swap(activate, other.activate);
    return *this;
  }
};

auto init_segtree(const int n) {
  struct node {
    int64 sum = 0;
    int64 size = 0;
    int64 lazy = 0;
  };

  vector<node> a(n);
  for (node &x : a) x.size = 1;

  auto unite = [](const node &l, const node &r) {
    node ans;
    ans.sum = l.sum + r.sum;
    ans.size = l.size + r.size;
    return ans;
  };

  auto apply = [](node &x, const node &upd) {
    x.sum += upd.lazy * x.size;
    x.lazy += upd.lazy;
  };

  auto activate = [](node &x) {
    x.lazy = 0;
  };

  return LazySegTree<node>(a, unite, apply, activate);
}

struct query {
  int i;
  int l;
  int r;
  int64 ans;
};

struct range {
  int l;
  int r;
};

inline void solution() {
  const int n = Read::Int();
  const int q = Read::Int();

  vector<int> a = Read::Vec<int>(n);

  vector<query> queries(q);
  for (int i = 0; i < q; i++) {
    const int l = Read::Int() - 1;
    const int r = Read::Int() - 1;
    queries[i].i = i;
    queries[i].l = l;
    queries[i].r = r;
  }

  sort(queries.begin(), queries.end(), [](const query &q1, const query &q2) {
    return q1.l > q2.l;
  });

  auto lst = init_segtree(n);
  vector<pair<int, range>> stk;

  auto add = [&](const int i) {
    range cur{i, i};
    while (not stk.empty() and stk.back().first <= a[i]) {
      const auto [x, scope] = stk.back();
      lst.update(scope.l, scope.r, {0, 0, a[i] - x});
      cur.r = scope.r;
      stk.pop_back();
    }
    stk.emplace_back(a[i], cur);
  };

  for (int i = n - 1; auto &[_, l, r, ans] : queries) {
    while (l <= i) {
      add(i--);
    }
    ans = lst.query(l, r).sum;
  }

  sort(queries.begin(), queries.end(), [](const query &q1, const query &q2) {
    return q1.i < q2.i;
  });

  for (const auto &[i, l, r, ans] : queries) {
    cout << ans << '\n';
  }
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