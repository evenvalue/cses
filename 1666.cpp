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
  vector<int> visit(n);
  function<void(const int)> dfs = [&](const int x) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (visit[y]) continue;
      dfs(y);
    }
  };
  dfs(0);
  int comp = 1;
  vector<int> node;
  for (int i = 1; i < n; i++) {
    if (not visit[i]) {
      dfs(i);
      node.push_back(i);
      comp++;
    }
  }
  cout << comp - 1 << "\n";
  for (int i = 0; i < comp - 1; i++) {
    cout << 1 << " " << node[i] + 1 << "\n";
  }
}