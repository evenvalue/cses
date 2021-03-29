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
  vector<vector<bool>> visit(n, vector<bool>(m));
  pair<int, int> s, f;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      cin >> c;
      visit[i][j] = (c == '#');
      if (c == 'A') {
        s = {i, j};
      } else if (c == 'B') {
        f = {i, j};
      }
    }
  }
  vector<pair<int, int>> diff = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  vector<vector<pair<int, int>>> p(n, vector<pair<int, int>>(m, {-1, -1}));
  queue<pair<int, int>> q;
  visit[s.first][s.second] = true;
  q.push(s);
  while (not q.empty()) {
    const pair<int, int> x = q.front();
    q.pop();
    for (const auto nbr : diff) {
      int i = nbr.first + x.first;
      int j = nbr.second + x.second;
      if (i < 0 or j < 0 or n - 1 < i or m - 1 < j) continue;
      if (visit[i][j]) continue;
      p[i][j] = x;
      q.push({i, j});
      visit[i][j] = true;
    }
  }

  if (p[f.first][f.second] == make_pair(-1, -1)) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  string ans;
  for (pair<int, int> node = f; node != s; node = p[node.first][node.second]) {
    const pair<int, int> par = p[node.first][node.second];
    const int y = par.first - node.first;
    const int x = par.second - node.second;
    const pair<int, int> direc = {y, x};
    if (direc == make_pair(0, 1)) {
      ans.push_back('L');
    } else if (direc == make_pair(0, -1)) {
      ans.push_back('R');
    } else if (direc == make_pair(1, 0)) {
      ans.push_back('U');
    } else {
      ans.push_back('D');
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  cout << ans;
}