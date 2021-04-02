#include <iostream>
#include <vector>
using namespace std;

class SegTree {
  vector<int> t;

  static int unite(const int l, const int r) {
    return l + r;
  }

public:
  explicit SegTree(const int n) : t(2 * n - 1) {}

  void build(const int x, const int l, const int r) {
    if (l == r) {
      t[x] = 1;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid);
    build(y, mid + 1, r);
    t[x] = unite(t[x + 1], t[y]);
  }

  int query(const int x, const int l, const int r, int need) {
    t[x]--;
    if (l == r) {
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (t[x + 1] >= need) {
      return query(x + 1, l, mid, need);
    } else {
      need -= t[x + 1];
      return query(y, mid + 1, r, need);
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  SegTree st(n);
  st.build(0, 0, n - 1);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cout << a[st.query(0, 0, n - 1, x)] << " ";
  }
}