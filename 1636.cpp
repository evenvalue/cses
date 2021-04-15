#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9 + 7;

  int n, req;
  cin >> n >> req;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
  }
  vector<vector<int>> dp(n, vector<int>(req + 1, 0));
  for (int x = 0; x <= req; x++) {
    dp[0][x] = (x % coins[0] == 0);
  }
  for (int c = 0; c < n; c++) {
    dp[c][0] = 1;
  }
  for (int c = 1; c < n; c++) {
    for (int x = 1; x <= req; x++) {
      dp[c][x] = dp[c - 1][x];
      const int prev = x - coins[c];
      if (prev < 0) continue;
      dp[c][x] += dp[c][prev];
      dp[c][x] %= mod;
    }
  }
  cout << dp[n - 1][req] << "\n";
}