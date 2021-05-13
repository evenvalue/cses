#include <iostream>
#include <set>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  multiset<int> s;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    s.insert(x);
  }
  s.insert(1e9 + 10);
  while (m--) {
    int q;
    cin >> q;
    auto it = s.upper_bound(q);
    if (it == s.begin()) {
      cout << -1 << "\n";
      continue;
    }
    it = prev(it);
    cout << *it << "\n";
    s.erase(it);
  }
}