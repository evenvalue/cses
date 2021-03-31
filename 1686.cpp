#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

struct SCC {
  vector<int> comp;
  int count = 0;
};

SCC kosaraju(const vector<vector<int>> &g, const vector<vector<int>> &gr) {
  const int n = g.size();
  vector<int> order;
  vector<bool> visit(n);
  function<void(int)> dfs1 = [&](const int x) {
    visit[x] = true;
    for (const int y : g[x]) {
      if (visit[y]) continue;
      dfs1(y);
    }
    order.push_back(x);
  };
  for (int i = 0; i < n; i++) {
    if (not visit[i]) {
      dfs1(i);
    }
  }
  vector<int> comp(n, -1);
  int scc = 0;
  function<void(int)> dfs2 = [&](const int x) {
    visit[x] = true;
    comp[x] = scc;
    for (const int y : gr[x]) {
      if (comp[y] == -1) {
        dfs2(y);
      }
    }
  };
  while (not order.empty()) {
    const int x = order.back();
    order.pop_back();
    if (comp[x] == -1) {
      dfs2(x);
      scc++;
    }
  }
  return {comp, scc};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<int64> room(n);
  for (int64 &coin : room) {
    cin >> coin;
  }
  vector<vector<int>> g(n), gr(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    gr[y - 1].push_back(x - 1);
  }
  SCC scc = kosaraju(g, gr);
  vector<vector<int>> g2(scc.count);
  vector<int64> coins(scc.count, 0);
  for (int x = 0; x < n; x++) {
    coins[scc.comp[x]] += room[x];
    for (const int y : g[x]) {
      if (scc.comp[y] == scc.comp[x]) continue;
      g2[scc.comp[x]].push_back(scc.comp[y]);
    }
  }
  vector<bool> visit(scc.count, false);
  function<void(int)> dfs = [&](const int x) {
    visit[x] = true;
    int64 res = 0;
    for (const int y : g2[x]) {
      if (not visit[y]) {
        dfs(y);
      }
      res = max(res, coins[y]);
    }
    coins[x] += res;
  };
  for (int i = 0; i < scc.count; i++) {
    if (not visit[i]) {
      dfs(i);
    }
  }
  cout << *max_element(coins.begin(), coins.end()) << "\n";
}