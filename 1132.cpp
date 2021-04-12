#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int bfs(const vector<vector<int>> &g, vector<int> &d, const int s) {
  const int n = g.size();
  vector<bool> visit(n, false);
  d[s] = 0;
  queue<int> q;
  q.push(s);
  while (not q.empty()) {
    int x = q.front();
    q.pop();
    visit[x] = true;
    for (int nbr : g[x]) {
      if (visit[nbr]) continue;
      q.push(nbr);
      d[nbr] = d[x] + 1;
    }
  }
  int far = distance(d.begin(), max_element(d.begin(), d.end()));
  return far;
}

pair<int, int> diameter(const vector<vector<int>> &g) {
  vector<int> d(g.size());
  int x = bfs(g, d, 0);
  int y = bfs(g, d, x);
  return {x, y};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  vector<int> dx(n);
  vector<int> dy(n);
  pair<int, int> endp = diameter(g);
  bfs(g, dx, endp.first);
  bfs(g, dy, endp.second);
  for (int i = 0; i < n; i++) {
    cout << max(dx[i], dy[i]) << " ";
  }
}