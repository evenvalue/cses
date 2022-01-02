#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

using int64 = int64_t;
using ld = long double;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

[[maybe_unused]] int readInt() {
  int x;
  cin >> x;
  return x;
}
[[maybe_unused]] int64 readInt64() {
  int64 x;
  cin >> x;
  return x;
}
[[maybe_unused]] char readChar() {
  char c;
  cin >> c;
  return c;
}
[[maybe_unused]] string readString() {
  string s;
  cin >> s;
  return s;
}
[[maybe_unused]] double readDouble() {
  return stod(readString());
}
[[maybe_unused]] ld readLongDouble() {
  return stold(readString());
}
template<typename T1, typename T2>
[[maybe_unused]] pair<T1, T2> readPair() {
  pair<T1, T2> p;
  cin >> p.first >> p.second;
  return p;
}
template<typename T>
[[maybe_unused]] vector<T> readVec(const int sz) {
  vector<T> v(sz);
  for (T &x : v) {
    cin >> x;
  }
  return v;
}
template<typename T>
[[maybe_unused]] vector<vector<T>> readVecVec(const int n, const int m) {
  vector<vector<T>> a(n);
  for (vector<T> &v : a) {
    v = readVec<T>(m);
  }
  return a;
}

const int64 kInf64 = 2e18 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

struct customer {
  int idx;
  int in, out;

  bool operator>(const customer &other) const {
    return (in != other.in ? in > other.in : out > other.out);
  }
};

void solution() {
  const int n = readInt();

  min_heap<int> free; //holds the index of rooms that are free.
  min_heap<customer> customers; //holds the customers.
  min_heap<pair<int, int>> future_free; //holds the rooms that will free in the future.

  for (int i = 1; i <= n; i++) {
    free.push(i); //ith room is currently free at time 0.
  }

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    const int in = readInt(), out = readInt();
    customers.push({i, in, out}); //Add new customer.
  }

  for (int time = customers.top().in; not customers.empty();) {
    time = customers.top().in;
    while (not future_free.empty() and future_free.top().first <= time) { //While there is a room that is already free but not in the heap free...
      const auto [_, r] = future_free.top();
      free.push(r); //Push it to free.
      future_free.pop(); //And pop it from future free.
    }
    const auto [i, in, out] = customers.top();
    const int room = free.top();
    ans[i] = room;
    future_free.push({out + 1, room}); //The room will become free only after the ith customer moves out.
    customers.pop(), free.pop(); //The customer has been assigned his room, so we pop from the heaps.
  }
  cout << *max_element(ans.begin(), ans.end()) << '\n';
  for (const int x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const auto begin = std::chrono::high_resolution_clock::now();

  //  freopen(".in", "r", stdin);
  //  freopen(".out", "w", stdout);

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solution();
  }

  const auto end = std::chrono::high_resolution_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}