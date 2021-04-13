#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

class SegTree {
  vector<int64> t;

  static int64 unite(const int64 l, const int64 r) {
    return l + r;
  }

public:
  explicit SegTree(const int n) : t(2 * n - 1) {}

  void update(const int x, const int l, const int r, const int pos, const int upd) {
    if (l == r) {
      t[x] = upd;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      update(x + 1, l, mid, pos, upd);
    } else {
      update(y, mid + 1, r, pos, upd);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  int64 query(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid + 1 <= ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr), query(y, mid + 1, r, ql, qr));
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  struct node {
    int value;
    int l, r;
  };

  int n, q;
  cin >> n >> q;
  vector<node> a(n);
  for (node &x : a) {
    cin >> x.value;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  int timer = 0;
  function<void(int, int)> dfs = [&](const int x, const int p) {
    a[x].l = timer;
    timer++;
    for (const int &y : g[x]) {
      if (y == p) continue;
      dfs(y, x);
    }
    a[x].r = timer - 1;
  };
  dfs(0, -1);
  SegTree st(n);
  for (const node &x : a) {
    st.update(0, 0, n - 1, x.l, x.value);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int vertex, upd;
      cin >> vertex >> upd;
      vertex--;
      a[vertex].value = upd;
      st.update(0, 0, n - 1, a[vertex].l, upd);
    } else {
      int vertex;
      cin >> vertex;
      vertex--;
      cout << st.query(0, 0, n - 1, a[vertex].l, a[vertex].r) << "\n";
    }
  }
}