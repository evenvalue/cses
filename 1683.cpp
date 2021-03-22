#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n), gr(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    gr[y - 1].push_back(x - 1);
  }
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
  vector<int> ans(n);
  int comp = 0;
  function<void(const int)> dfs2 = [&](const int x) {
    visit[x] = true;
    ans[x] = comp;
    for (const int y : gr[x]) {
      if (visit[y]) continue;
      dfs2(y);
    }
  };
  for (int i = 0; i < n; i++) {
    if (not visit[i]) {
      dfs1(i);
    }
  }
  visit.assign(n, false);
  while (not order.empty()) {
    const int x = order.back();
    order.pop_back();
    if (not visit[x]) {
      dfs2(x);
      comp++;
    }
  }
  cout << comp << "\n";
  for (const int x : ans) {
    cout << x + 1 << " ";
  }
  cout << "\n";
}