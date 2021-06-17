#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
  }
  vector<bool> visit(n, false);
  vector<int> topsort;
  topsort.reserve(n);
  function<void(int)> dfs = [&](const int x) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (visit[y]) continue;
      dfs(y);
    }
    topsort.push_back(x);
  };
  for (int x = 0; x < n; x++) {
    if (visit[x]) continue;
    dfs(x);
  }
  reverse(topsort.begin(), topsort.end());
  vector<int> ways(n);
  ways[0] = 1;
  for (const int x : topsort) {
    for (const int y : g[x]) {
      ways[y] += ways[x];
      ways[y] %= kMod;
    }
  }
  cout << ways[n - 1] << '\n';
}