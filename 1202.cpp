#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define int64 int64_t
#define debug(x) cerr << #x << ": " << x << '\n'

const int64 kInfL = 1e15 + 10;
const int kMod = 1e9 + 7;

struct info {
  int64 d = kInfL;
  int way = 0;
  int mn = 1e9 + 10;
  int mx = 0;
};

vector<info> dijkstra(const vector<vector<pair<int, int>>> &g, const int s) {
  const int n = g.size();
  vector<info> give(n);
  give[s] = {0, 1, 0, 0};
  set<pair<int64, int>> q;
  q.insert({0, s});
  while (not q.empty()) {
    const int x = q.begin()->second;
    q.erase(q.begin());
    for (const auto [y, w] : g[x]) {
      if (give[x].d + w > give[y].d) continue;
      if (give[x].d + w == give[y].d) {
        give[y].way = (give[y].way + give[x].way) % kMod;
        give[y].mn = min(give[y].mn, give[x].mn + 1);
        give[y].mx = max(give[y].mx, give[x].mx + 1);
      } else {
        q.erase({give[y].d, y});
        give[y].d = give[x].d + w;
        give[y].way = give[x].way;
        give[y].mn = give[x].mn + 1;
        give[y].mx = give[x].mx + 1;
        q.insert({give[y].d, y});
      }
    }
  }
  return give;
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    g[x - 1].push_back({y - 1, w});
  }
  const info ans = dijkstra(g, 0)[n - 1];
  cout << ans.d << ' ' << ans.way << ' ' << ans.mn << ' ' << ans.mx;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
    cout << '\n';
  }
}