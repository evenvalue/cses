#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int x = 1; x < n; x++) {
    int p;
    cin >> p;
    g[p - 1].push_back(x);
  }
  vector<int> sub(n, 1);
  function<int(int)> dfs = [&](const int x) {
    for (const int y : g[x]) {
      sub[x] += dfs(y);
    }
    return sub[x];
  };
  dfs(0);
  for (const int x : sub) {
    cout << x - 1 << " ";
  }
}