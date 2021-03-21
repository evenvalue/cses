#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n), gr(n);
  vector<bool> visit(n, false);
  vector<int> order;
  function<void(const int)> dfs1 = [&](const int x) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (visit[y]) continue;
      dfs1(y);
    }
    order.push_back(x);
  };

  vector<int> comp;
  function<void(const int)> dfs2 = [&](const int x) {
    visit[x] = true;
    comp.push_back(x);
    for (const int y : gr[x]) {
      if (visit[y]) continue;
      dfs2(y);
    }
  };

  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    gr[y - 1].push_back(x - 1);
  }

  auto reject = [](const int x, const int y) {
    cout << "NO\n";
    cout << x << " " << y << "\n";
    exit(0);
  };

  dfs1(0);
  for (int i = 1; i < n; i++) {
    if (not visit[i]) {
      reject(1, i + 1);
    }
  }
  visit.assign(n, false);
  dfs2(order[n - 1]);
  for (int i = 0; i < n; i++) {
    const int x = order[n - i - 1];
    if (not visit[x]) {
      reject(x + 1, order[n - 1] + 1);
    }
  }
  cout << "YES\n";
}