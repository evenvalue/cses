#include <iostream>
#include <functional>
#include <set>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kInf = 1e9 + 10;

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
  vector<int> d(n, -kInf);
  vector<int> p(n, -1);
  d[0] = 0;
  for (const int x : topsort) {
    for (const int y : g[x]) {
      if (d[y] >= d[x] + 1) continue;
      d[y] = d[x] + 1;
      p[y] = x;
    }
  }
  if (d[n - 1] < 0) {
    cout << "IMPOSSIBLE\n";
  } else {
    vector<int> ans;
    ans.reserve(d[n - 1] + 1);
    for (int x = n - 1; x != -1; x = p[x]) {
      ans.push_back(x);
    }
    reverse(ans.begin(), ans.end());
    cout << d[n - 1] + 1 << '\n';
    for (const int &x : ans) {
      cout << x + 1 << ' ';
    }
    cout << '\n';
  }
}