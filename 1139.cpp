#include <functional>
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
  explicit SegTree(const int n) : t(2 * n - 1) {}

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

struct node {
  int idx;
  int colour;
  int ans;
  int l, r;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<node> a(n);
  map<int, int> last_occ;
  for (int i = 0; i < n; i++) {
    a[i].idx = i;
    cin >> a[i].colour;
    last_occ[a[i].colour] = -1;
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
    for (const int &y : g[x]) {
      if (y == p) continue;
      dfs(y, x);
    }
    a[x].r = timer;
    timer++;
  };
  dfs(0, -1);
  sort(a.begin(), a.end(), [](const node &x, const node &y) {
    return x.r < y.r;
  });
  SegTree st(n);
  for (int i = 0, j = 0; i < n and j < n; i++) {
    if (last_occ[a[i].colour] != -1) {
      st.update(0, 0, n - 1, last_occ[a[i].colour]);
    }
    last_occ[a[i].colour] = i;
    st.update(0, 0, n - 1, i);
    while (j < n and a[j].r == i) {
      a[j].ans = st.query(0, 0, n - 1, a[i].l, a[i].r);
      j++;
    }
  }
  sort(a.begin(), a.end(), [](const node &x, const node &y) {
    return x.idx < y.idx;
  });
  for (const node &x : a) {
    cout << x.ans << " ";
  }
}