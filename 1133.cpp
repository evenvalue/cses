#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  vector<int> size(n, 1);
  vector<int64> subsum(n);
  function<void(int, int)> dfs1 = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      dfs1(y, x);
      size[x] += size[y];
      subsum[x] += subsum[y] + size[y];
    }
  };
  dfs1(0, -1);
  vector<int64> ans(n);
  function<void(int, int)> dfs2 = [&](const int x, const int p) {
    for (const int &y : g[x]) {
      if (y == p) continue;
      ans[y] = ans[x] - 2 * size[y] + n;
      dfs2(y, x);
    }
  };
  ans[0] = subsum[0];
  dfs2(0, -1);
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " ";
  }
}