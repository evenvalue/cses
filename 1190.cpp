#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

struct node {
  int64 sum = 0;
  int64 pref = 0;
  int64 suff = 0;
  int64 best = 0;
};

class SegTree {
  vector<node> t;

  static node unite(const node &l, const node &r) {
    node ans;
    ans.sum = l.sum + r.sum;
    ans.pref = max(l.pref, l.sum + r.pref);
    ans.suff = max(l.suff + r.sum, r.suff);
    ans.best = max({l.best, r.best, l.suff + r.pref});
    return ans;
  }

public:
  explicit SegTree(const int n) : t(2 * n - 1) {}

  void build(const int x, const int l, const int r, const vector<int> &a) {
    if (l == r) {
      t[x].sum = a[l];
      t[x].pref = t[x].suff = t[x].best = max(a[l], 0);
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  node update(const int x, const int l, const int r, const int pos, const int upd) {
    if (l == r) {
      t[x].sum = upd;
      t[x].pref = t[x].suff = t[x].best = max(upd, 0);
      return t[x];
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      update(x + 1, l, mid, pos, upd);
    } else {
      update(y, mid + 1, r, pos, upd);
    }
    t[x] = unite(t[x + 1], t[y]);
    return t[x];
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
    int pos, upd;
    cin >> pos >> upd;
    cout << st.update(0, 0, n - 1, pos - 1, upd).best << "\n";
  }
}