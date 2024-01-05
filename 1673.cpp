#include <bits/stdc++.h>
using namespace std;

#ifdef evenvalue
  #include "debug.h"
#else
  #define debug(...)
#endif

using int64 = long long;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

namespace read {
int Int() {
  int x;
  cin >> x;
  return x;
}
int64 Int64() {
  int64 x;
  cin >> x;
  return x;
}
char Char() {
  char c;
  cin >> c;
  return c;
}
string String() {
  string s;
  cin >> s;
  return s;
}
double Double() {
  return stod(String());
}
ld LongDouble() {
  return stold(String());
}
template<typename T1, typename T2>
pair<T1, T2> Pair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
vector<T> Vec(const int n) {
  vector<T> v(n);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
vector<vector<T>> VecVec(const int n, const int m) {
  vector<vector<T>> v(n);
  for (vector<T> &vec : v) {
    vec = Vec<T>(m);
  }
  return v;
}
}//namespace read

constexpr int kInf = 1e9 + 10;
constexpr int64 kInf64 = 1e17;
constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 2e5 + 10;

struct edge {
  int x;
  int y;
  int w;
};

inline void solution() {
  const int n = read::Int();
  const int m = read::Int();

  vector<edge> edges(m);
  for (auto &[x, y, w] : edges) {
    x = read::Int() - 1;
    y = read::Int() - 1;
    w = read::Int();
  }

  vector<int64> dist(n, -kInf64);
  dist[0] = 0;

  for (int i = 0; i < n; i++) {
    for (const auto &[x, y, w] : edges) {
      if (dist[x] == -kInf64) continue;
      dist[y] = max(dist[y], dist[x] + w);
    }
  }

  for (int i = 0; i < n; i++) {
    for (const auto &[x, y, w] : edges) {
      if (dist[x] == -kInf64) continue;
      if (dist[y] < dist[x] + w) {
        dist[y] = kInf64;
      }
    }
  }

  cout << (dist[n - 1] == kInf64 ? -1 : dist[n - 1]) << '\n';
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