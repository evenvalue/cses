#include <iostream>
#include <vector>
#include <functional>
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
    g[y - 1].push_back(x - 1);
  }
  vector<int> par(n, -1);
  vector<bool> visit(n, false);
  int cs = -1, ce = -1;
  function<bool(const int, const int)> dfs_cycle = [&](const int x, const int p) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (y == p) continue;
      if (visit[y]) {
        cs = y;
        ce = x;
        return true;
      }
      par[y] = x;
      if (dfs_cycle(y, x)) return true;
    }
    return false;
  };
  for (int i = 0; i < n; i++) {
    if (not visit[i] and dfs_cycle(i, -1)) {
      vector<int> ans;
      for (int x = ce; x != par[cs]; x = par[x]) {
        ans.push_back(x + 1);
      }
      ans.push_back(ce + 1);
      cout << ans.size() << "\n";
      for (const int x : ans) {
        cout << x << " ";
      }
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
}