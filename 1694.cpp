#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

template<typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

template<typename T1, typename T2>
pair<T1, T2> read_pair() {
  pair<T1, T2> p;
  cin >> p.first;
  cin >> p.second;
  return p;
}

template<typename T>
vector<T> read_vec(const int n, const int index = 0) {
  vector<T> v(n + index);
  for (int i = index; i < n + index; i++) {
    v[i] = read<T>();
  }
  return v;
}

template<typename T>
vector<vector<T>> read_vec_vec(const int n, const int m, const int index_n = 0, const int index_m = 0) {
  vector<vector<T>> grid(n + index_n);
  for (int i = index_n; i < n + index_n; i++) {
    grid[i] = read_vec<T>(m, index_m);
  }
  return grid;
}

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e15 + 10;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

struct FlowEdge {
  int v, u;
  long long cap, flow = 0;
  FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
  const long long flow_inf = 1e18;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, long long fwd, long long bwd) {
    edges.emplace_back(v, u, fwd);
    edges.emplace_back(u, v, bwd);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
        if (edges[id].cap == edges[id].flow)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  long long dfs(int v, long long pushed) {
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u = edges[id].u;
      if (level[v] + 1 != level[u])
        continue;
      long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  long long flow() {
    long long f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }
};

inline void solution() {
  const int n = read<int>();
  const int m = read<int>();

  Dinic g(n, 0, n - 1);
  for (int i = 0; i < m; i++) {
    const int x = read<int>() - 1;
    const int y = read<int>() - 1;
    const int w = read<int>();
    g.add_edge(x, y, w, 0);
  }

  cout << g.flow() << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);

  cout << fixed << setprecision(10);

  int testcases = 1;
  //cin >> testcases;
  while (testcases--) {
    solution();
  }
}