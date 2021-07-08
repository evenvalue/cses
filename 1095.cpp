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

int bin_pow(int64 a, int b) {
  int64 res = 1;
  while (b) {
    if (b & 1) res = (res * a) % kMod;
    a = (a * a) % kMod;
    b >>= 1;
  }
  return res;
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << bin_pow(a, b);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    cout << '\n';
  }
}