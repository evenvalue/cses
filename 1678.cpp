#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
  }
  vector<int> colour(n, 0);
  vector<int> par(n, -1);
  int cs = -1, ce = -1;
  function<bool(int)> dfs_cycle = [&](int x) {
    colour[x] = 1;
    for (const int y : g[x]) {
      if (colour[y] == 2) continue;
      if (colour[y] == 0) {
        par[y] = x;
        if (dfs_cycle(y)) return true;
      } else {
        cs = y;
        ce = x;
        return true;
      }
    }
    colour[x] = 2;
    return false;
  };
  for (int i = 0; i < n; i++) {
    if (colour[i] == 0 and dfs_cycle(i)) {
      vector<int> ans;
      for (int x = ce; x != par[cs]; x = par[x]) {
        ans.push_back(x + 1);
      }
      ans.push_back(ce + 1);
      reverse(ans.begin(), ans.end());
      cout << ans.size() << "\n";
      for (int &x : ans) {
        cout << x << " ";
      }
      cout << "\n";
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
}