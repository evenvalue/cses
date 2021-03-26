#include <iostream>
#include <functional>
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
    g[y - 1].push_back(x - 1);
  }
  auto reject = []() {
    cout << "IMPOSSIBLE\n";
    exit(0);
  };
  vector<int> clr(n, -1);
  function<void(const int)> dfs = [&](const int x) {
    for (const int y : g[x]) {
      if (clr[y] == -1) {
        clr[y] = 1 - clr[x];
        dfs(y);
      }
      if (clr[x] != 1 - clr[y]) reject();
    }
  };
  for (int i = 0; i < n; i++) {
    if (clr[i] == -1) {
      clr[i] = 0;
      dfs(i);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << clr[i] + 1 << " ";
  }
  cout << "\n";
}