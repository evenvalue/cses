#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

struct node {
  int64 value = 0;
  int64 lazy = 0;
};

class SegTree {
  vector<node> t;

  static node unite(const node l, const node r) {
    return {l.value + r.value, 0};
  }

  void push(const int x, const int l, const int r) {
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    int64 &lazy = t[x].lazy;
    t[x + 1].value += lazy;
    t[y].value += lazy;
    t[x + 1].lazy += lazy;
    t[y].lazy += lazy;
    lazy = 0;
  }

public:
  explicit SegTree(const int n) : t(2 * n - 1) {}

  void build(const int x, const int l, const int r, const vector<int> &a) {
    if (l == r) {
      t[x].value = a[l];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  void update(const int x, const int l, const int r, const int ql, const int qr, const int u) {
    if (ql <= l and r <= qr) {
      t[x].value += u;
      t[x].lazy += u;
      return;
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (ql <= mid) {
      update(x + 1, l, mid, ql, qr, u);
    }
    if (mid + 1 <= qr) {
      update(y, mid + 1, r, ql, qr, u);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  node query(const int x, const int l, const int r, const int pos) {
    if (l == r) {
      return t[x];
    }
    push(x, l, r);
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      return query(x + 1, l, mid, pos);
    } else {
      return query(y, mid + 1, r, pos);
    }
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  SegTree st(n);
  st.build(0, 0, n - 1, a);
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r, u;
      cin >> l >> r >> u;
      st.update(0, 0, n - 1, l - 1, r - 1, u);
    } else {
      int pos;
      cin >> pos;
      cout << st.query(0, 0, n - 1, pos - 1).value << "\n";
    }
  }
}