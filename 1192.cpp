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
  vector<vector<bool>> building(n, vector<bool>(m));
  for (auto &floor : building) {
    for (int i = 0; i < m; i++) {
      char c;
      cin >> c;
      floor[i] = (c == '#');
    }
  }
  const vector<pair<int, int>> diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  function<void(const int, const int)> dfs = [&](const int x, const int y) {
    building[x][y] = true;
    for (auto nbr : diff) {
      nbr.first += x;
      nbr.second += y;
      if (nbr.first < 0 or n <= nbr.first) continue;
      if (nbr.second < 0 or m <= nbr.second) continue;
      if (building[nbr.first][nbr.second]) continue;
      dfs(nbr.first, nbr.second);
    }
  };
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (not building[i][j]) {
        dfs(i, j);
        ans++;
      }
    }
  }
  cout << ans << "\n";
}