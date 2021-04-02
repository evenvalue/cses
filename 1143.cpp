#include <iostream>
#include <vector>
using namespace std;

class SegTree {
  vector<int> t;

  static int unite(const int l, const int r) {
    return max(l, r);
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

  int find_first(const int x, const int l, const int r, int need) {
    if(t[x] < need) {
      return -1;
    }
    if (l == r) {
      t[x] -= need;
      return l;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    int res;
    if (t[x + 1] >= need) {
      res = find_first(x + 1, l, mid, need);
    } else {
      res = find_first(y, mid + 1, r, need);
    }
    t[x] = unite(t[x + 1], t[y]);
    return res;
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
    int x;
    cin >> x;
    cout << st.find_first(0, 0, n - 1, x) + 1 << " ";
  }
}