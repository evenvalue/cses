#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  vector<bool> taken(n);
  function<void(int, int)> dfs = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      dfs(y, x);
    }
    if (p == -1 or taken[x] or taken[p]) return;
    taken[x] = taken[p] = true;
  };
  dfs(0, -1);
  cout << count(taken.begin(), taken.end(), true) / 2 << "\n";
}