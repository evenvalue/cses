#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

pair<int, int> diameter(const vector<vector<int>> &g) {
  auto bfs = [&](int start) -> int {
    const int n = g.size();
    vector<int> d(n, 0);
    vector<bool> visit(n, false);
    queue<int> q;
    q.push(start);
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
  };
  int x = bfs(0);
  int y = bfs(x);
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

  auto bfs = [&](vector<int> &d, int start) {
    const int n = g.size();
    vector<bool> visit(n, false);
    queue<int> q;
    q.push(start);
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
  };
  vector<int> dx(n);
  vector<int> dy(n);
  pair<int, int> endp = diameter(g);
  bfs(dx, endp.first);
  bfs(dy, endp.second);
  for (int i = 0; i < n; i++) {
    cout << max(dx[i], dy[i]) << " ";
  }
}