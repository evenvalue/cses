#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int diameter(const vector<vector<int>> &g) {
  auto bfs = [&](int start) -> pair<int, int> {
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
    return {d[far], far};
  };
  int x = bfs(0).second;
  return bfs(x).first;
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
  cout << diameter(g) << "\n";
}