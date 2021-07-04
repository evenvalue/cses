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

void gen(const int mask, const int i, const int nxt_mask, const int n, vector<int> &masks) {
  if (i == n) {
    masks.push_back(nxt_mask);
    return;
  }
  if ((mask & (1 << i)) != 0) {
    gen(mask, i + 1, nxt_mask, n, masks);
    return;
  }
  if (i != (n - 1) and (mask & (1 << (i + 1))) == 0) {
    gen(mask, i + 2, nxt_mask, n, masks);
  }
  gen(mask, i + 1, nxt_mask | (1 << i), n, masks);
}


int solve(vector<vector<int>> &ways, const int n, const int m, const int mask, const int c) {
  if (c == m) {
    return (mask == 0);
  }
  if (ways[mask][c] != -1) return ways[mask][c];
  vector<int> masks;
  gen(mask, 0, 0, n, masks);
  int ans = 0;
  for (const int nxt_mask : masks) {
    ans += solve(ways, n, m, nxt_mask, c + 1);
    ans %= kMod;
  }
  return (ways[mask][c] = ans);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ways(1 << (n + 1), vector<int>(m, -1));
    cout << solve(ways, n, m, 0, 0) << '\n';
  }
}