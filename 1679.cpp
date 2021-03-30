#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
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
  vector<int> topsort;
  vector<bool> visit(n, false), enter(n, false);

  auto reject = []() {
    cout << "IMPOSSIBLE\n";
    exit(0);
  };

  function<void(const int)> dfs = [&](const int x) {
    visit[x] = enter[x] = true;
    for (const int y : g[x]) {
      if (enter[y]) reject();
      if (visit[y]) continue;
      dfs(y);
    }
    topsort.push_back(x);
    enter[x] = false;
  };
  for (int i = 0; i < n; i++) {
    if (not visit[i]) {
      dfs(i);
    }
  }
  reverse(topsort.begin(), topsort.end());
  for (const int x : topsort) {
    cout << x + 1 << " ";
  }
  cout << "\n";
}