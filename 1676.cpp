#include <iostream>
#include <vector>
using namespace std;

class dsu {
  vector<int> e;

public:
  explicit dsu(const int n) : e(n, -1) {}

  int find(const int x) {
    return e[x] < 0 ? x : (e[x] = find(e[x]));
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return true;
  }

  int size(const int x) {
    return -e[find(x)];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  dsu comp(n);
  int components = n, size = 1;
  while (m--) {
    int x, y;
    cin >> x >> y;
    if (comp.unite(x - 1, y - 1)) {
      components--;
      size = max(size, comp.size(x - 1));
    }
    cout << components << " " << size << "\n";
  }
}