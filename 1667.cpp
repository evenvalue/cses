#include <algorithm>
#include <iostream>
#include <queue>
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
  vector<bool> visit(n, false);
  visit[0] = true;
  vector<int> par(n, -1);
  queue<int> q;
  q.push(0);
  while (not q.empty()) {
    const int x = q.front();
    q.pop();
    for (const int y : g[x]) {
      if (visit[y]) continue;
      par[y] = x;
      q.push(y);
      visit[y] = true;
    }
  }
  if (par[n - 1] == -1) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  vector<int> ans;
  for (int x = n - 1; x != -1; x = par[x]) {
    ans.push_back(x + 1);
  }
  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  for (const int x : ans) {
    cout << x << " ";
  }
  cout << "\n";
}