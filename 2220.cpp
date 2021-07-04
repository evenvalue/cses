#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#define int64 int64_t
#define debug(x) cerr << #x << ": " << x << '\n'

const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

int64 solve(int64 x) {
  string num = to_string(x);
  const int kPlaces = num.size();
  vector<int64> ways(kPlaces, 1);
  for (int p = 1; p < kPlaces; p++) {
    ways[p] = 9 * ways[p - 1];
  }
  int64 ans = 0;
  for (int p = 0; p < kPlaces - 1; p++) {
    ans += ways[p];
  }
  reverse(num.begin(), num.end());
  for (int p = kPlaces - 1, last_d = 10; p >= 0; p--) {
    const int digit = num[p] - '0';
    ans += (digit * ways[p]) - (last_d < digit ? ways[p] : 0);
    if (digit == last_d) break;
    last_d = digit;
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int64 a, b;
  cin >> a >> b;
  cout << solve(b + 1) - solve(a) << '\n';
}