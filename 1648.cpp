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

  void build(const int x, const int l, const int r, const vector<int> &a) {
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
      int pos, upd;
      cin >> pos >> upd;
      st.update(0, 0, n - 1, pos - 1, upd);
    } else {
      int l, r;
      cin >> l >> r;
      cout << st.query(0, 0, n - 1, l - 1, r - 1) << "\n";
    }
  }
}