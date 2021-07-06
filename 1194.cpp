#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

pair<vector<vector<int>>, vector<vector<pair<int, int>>>> bfs(const vector<vector<bool>> &grid, const vector<pair<int, int>> &start) {
  const int n = grid.size();
  const int m = grid[0].size();
  queue<pair<int, int>> q;
  vector<vector<int>> d(n, vector<int>(m, -1));
  vector<vector<pair<int, int>>> p(n, vector<pair<int, int>>(m, {-1, -1}));
  for (const pair<int, int> cell : start) {
    q.push(cell);
    d[cell.first][cell.second] = 0;
  }
  const vector<pair<int, int>> diff = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  while (not q.empty()) {
    const auto [x, y] = q.front();
    q.pop();
    for (const auto [dx, dy] : diff) {
      if (not grid[x + dx][y + dy] or d[x + dx][y + dy] != -1) continue;
      d[x + dx][y + dy] = d[x][y] + 1;
      p[x + dx][y + dy] = {x, y};
      q.push({x + dx, y + dy});
    }
  }
  return {d, p};
}

void change(int &x, int &y, const pair<int, int> &p) {
  x = p.first;
  y = p.second;
}

char dir(const int dx, const int dy) {
  if (dx == 0 and dy == 1) return 'R';
  if (dx == 0 and dy == -1) return 'L';
  if (dx == 1 and dy == 0) return 'D';
  if (dx == -1 and dy == 0) return 'U';
  else return '-';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<bool>> grid(n + 2, vector<bool>(m + 2, false));
  vector<pair<int, int>> monster;
  pair<int, int> me;
  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= m; y++) {
      char c;
      cin >> c;
      grid[x][y] = (c != '#');
      if (c == 'M') {
        monster.emplace_back(x, y);
      } else if (c == 'A') {
        me = {x, y};
      }
    }
  }
  const vector<vector<int>> &dm = bfs(grid, monster).first;
  const auto [da, p] = bfs(grid, {me});
  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= m; y++) {
      if ((x != 1 and x != n) and (y != 1 and y != m)) continue;
      if (da[x][y] == -1 or (dm[x][y] != -1 and dm[x][y] <= da[x][y])) continue;
      cout << "YES\n";
      cout << da[x][y] << '\n';
      string path;
      path.reserve(da[x][y]);
      for (; p[x][y] != make_pair(-1, -1); change(x, y, p[x][y])) {
        path.push_back(dir(x - p[x][y].first, y - p[x][y].second));
      }
      reverse(path.begin(), path.end());
      cout << path;
      return 0;
    }
  }
  cout << "NO";
}