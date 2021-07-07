#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#define int64 int64_t
#define debug(x) cerr << #x << ": " << x << '\n'

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  if (n * (n + 1) % 4) {
    cout << "NO\n";
    return;
  }
  vector<int> v;
  v.reserve(n);
  if (n & 1) {
    v.push_back(n);
    for (int i = 1, x = 1; i < (n + 1) / 4; i++, x++) {
      v.push_back(n - x);
      v.push_back(x);
    }
  } else {
    for (int i = 0, x = 0; i < n / 4; i++, x++) {
      v.push_back(n - x);
      v.push_back(x + 1);
    }
  }
  sort(v.begin(), v.end());
  cout << "YES\n";
  cout << v.size() << '\n';
  for (const int x : v) {
    cout << x << ' ';
  }
  cout << '\n' << n - v.size() << '\n';
  for (int x = 1, i = 0; x <= n; x++) {
    if (v[i] == x) i++;
    else {
      cout << x << ' ';
    }
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
  }
}