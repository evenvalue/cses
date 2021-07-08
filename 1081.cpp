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
  vector<int> a(n);
  int mx = 0;
  for (int &x : a) {
    cin >> x;
    mx = max(mx, x);
  }
  vector<int> div(mx + 1);
  for (const int x : a) {
    for (int j = 1; j * j <= x; j++) {
      if (x % j == 0) {
        div[j]++;
        if (j != x / j) div[x / j]++;
      }
    }
  }
  for (int g = mx; g >= 1; g--) {
    if (div[g] <= 1) continue;
    cout << g;
    return;
  }
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