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

template<typename T>
class graph {
public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  vector<edge> edges;
  vector<vector<int>> g;
  int n;

  graph(int n) : n(n) {
    g.resize(n);
  }

  virtual void add(int from, int to, T cost) = 0;
};

template<typename T>
class undigraph : public graph<T> {
public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  undigraph(int n) : graph<T>(n) {
  }

  void add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    g[from].push_back(edges.size());
    g[to].push_back(edges.size());
    edges.push_back({from, to, cost});
  }
};

template<typename T>
class forest : public graph<T> {
public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  forest(int n) : graph<T>(n) {
  }

  void add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    g[from].push_back(edges.size());
    g[to].push_back(edges.size());
    edges.push_back({from, to, cost});
  }
};

template<typename T>
class flow_graph {
public:
  static constexpr T eps = (T) 1e-9;

  struct edge {
    int to;
    T c;
    T f;
    int rev;
  };

  vector<vector<edge>> g;
  vector<int> ptr;
  vector<int> d;
  vector<int> q;
  vector<int> cnt_on_layer;
  vector<int> prev_edge;
  vector<T> to_push;
  vector<T> pushed;
  vector<int> smallest;
  bool can_reach_sink;

  int n;
  int st, fin;
  T flow;

  flow_graph(int n, int st, int fin) : n(n), st(st), fin(fin) {
    assert(0 <= st && st < n && 0 <= fin && fin < n && st != fin);
    g.resize(n);
    ptr.resize(n);
    d.resize(n);
    q.resize(n);
    cnt_on_layer.resize(n + 1);
    prev_edge.resize(n);
    to_push.resize(n);
    pushed.resize(n);
    smallest.resize(n);
    flow = 0;
  }

  void clear_flow() {
    for (int i = 0; i < n; i++) {
      for (edge &e : g[i]) {
        e.f = 0;
      }
    }
    flow = 0;
  }

  void add(int from, int to, T forward_cap, T backward_cap) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int from_size = g[from].size();
    int to_size = g[to].size();
    g[from].push_back({to, forward_cap, 0, to_size});
    g[to].push_back({from, backward_cap, 0, from_size});
  }

  bool expath() {
    fill(d.begin(), d.end(), n);
    q[0] = fin;
    d[fin] = 0;
    fill(cnt_on_layer.begin(), cnt_on_layer.end(), 0);
    cnt_on_layer[n] = n - 1;
    cnt_on_layer[0] = 1;
    int beg = 0, end = 1;
    while (beg < end) {
      int i = q[beg++];
      for (const edge &e : g[i]) {
        const edge &back = g[e.to][e.rev];
        if (back.c - back.f > eps && d[e.to] == n) {
          cnt_on_layer[d[e.to]]--;
          d[e.to] = d[i] + 1;
          cnt_on_layer[d[e.to]]++;
          q[end++] = e.to;
        }
      }
    }
    return (d[st] != n);
  }

  void rollback(int &v) {
    edge &e = g[v][prev_edge[v]];
    if (pushed[v]) {
      edge &back = g[e.to][e.rev];
      back.f += pushed[v];
      e.f -= pushed[v];
      pushed[e.to] += pushed[v];
      to_push[e.to] -= pushed[v];
      pushed[v] = 0;
    }
    v = e.to;
  }

  void augment(int &v) {
    pushed[v] += to_push[v];
    to_push[v] = 0;
    int new_v = smallest[v];
    while (v != new_v) {
      rollback(v);
    }
  }

  void retreat(int &v) {
    int new_dist = n - 1;
    for (const edge &e : g[v]) {
      if (e.c - e.f > eps && d[e.to] < new_dist) {
        new_dist = d[e.to];
      }
    }
    cnt_on_layer[d[v]]--;
    if (cnt_on_layer[d[v]] == 0) {
      if (new_dist + 1 > d[v]) {
        can_reach_sink = false;
      }
    }
    d[v] = new_dist + 1;
    cnt_on_layer[d[v]]++;
    if (v != st) {
      rollback(v);
    }
  }

  T max_flow() {
    can_reach_sink = true;
    for (int i = 0; i < n; i++) {
      ptr[i] = (int) g[i].size() - 1;
    }
    if (expath()) {
      int v = st;
      to_push[v] = numeric_limits<T>::max();
      smallest[v] = v;
      while (d[st] < n) {
        while (ptr[v] >= 0) {
          const edge &e = g[v][ptr[v]];
          if (e.c - e.f > eps && d[e.to] == d[v] - 1) {
            prev_edge[e.to] = e.rev;
            to_push[e.to] = to_push[v];
            smallest[e.to] = smallest[v];
            if (e.c - e.f < to_push[e.to]) {
              to_push[e.to] = e.c - e.f;
              smallest[e.to] = v;
            }
            v = e.to;
            if (v == fin) {
              augment(v);
            }
            break;
          }
          ptr[v]--;
        }
        if (ptr[v] < 0) {
          ptr[v] = (int) g[v].size() - 1;
          retreat(v);
          if (!can_reach_sink) {
            break;
          }
        }
      }
      while (v != st) {
        rollback(v);
      }
      flow += pushed[st];
      pushed[st] = 0;
    }
    return flow;
  }

  vector<bool> min_cut() {
    max_flow();
    assert(!expath());
    vector<bool> ret(n);
    for (int i = 0; i < n; i++) {
      ret[i] = (d[i] != n);
    }
    return ret;
  }
};

inline void solution() {
  const int n = read<int>();
  const int m = read<int>();
  const int k = read<int>();

  auto source = [&]() { return 0; };
  auto boy = [&](const int x) { return x; };
  auto girl = [&](const int x) { return n + x; };
  auto sink = [&]() { return n + m + 1; };

  flow_graph<int64> g(n + m + 2, source(), sink());

  for (int i = 0; i < k; i++) {
    const int x = read<int>();
    const int y = read<int>();
    g.add(boy(x), girl(y), kInf, 0);
  }

  for (int x = 1; x <= n; x++) {
    g.add(source(), boy(x), 1, 0);
  }

  for (int y = 1; y <= m; y++) {
    g.add(girl(y), sink(), 1, 0);
  }

  cout << g.max_flow() << '\n';
  for (int x = 1; x <= n; x++) {
    for (const auto e : g.g[x]) {
      if (e.f == 0 or e.to == 0) continue;
      cout << x << ' ' << e.to - n << '\n';
    }
  }
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