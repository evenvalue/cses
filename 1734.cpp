#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class SegTree {
  vector<int> t;

  static int unite(const int l, const int r) {
    return l + r;
  }

public:
  explicit SegTree(const int n) : t(2 * n - 1, 0) {}

  void update(const int x, const int l, const int r, const int pos) {
    if (l == r) {
      t[x] = 1 - t[x];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (pos <= mid) {
      update(x + 1, l, mid, pos);
    } else {
      update(y, mid + 1, r, pos);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  int query(const int x, const int l, const int r, const int ql, const int qr) {
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

struct query {
  int idx;
  int l;
  int r;
  int ans;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  vector<query> q(m);
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    q[i].idx = i;
    q[i].l = l - 1;
    q[i].r = r - 1;
  }
  sort(q.begin(), q.end(), [](const query q1, const query q2) {
    return q1.r < q2.r;
  });
  SegTree st(n);
  map<int, int> last_occ;
  for (int i = 0, j = 0; i < n and j < m; i++) {
    if (last_occ[a[i]] != 0) {
      st.update(0, 0, n - 1, last_occ[a[i]] - 1);
    }
    last_occ[a[i]] = i + 1;
    st.update(0, 0, n - 1, i);
    while (j < m and q[j].r == i) {
      q[j].ans = st.query(0, 0, n - 1, q[j].l, q[j].r);
      j++;
    }
  }
  sort(q.begin(), q.end(), [](const query q1, const query q2) {
    return q1.idx < q2.idx;
  });
  for (const query &qry : q) {
    cout << qry.ans << "\n";
  }
}