#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n, req;
  cin >> n >> req;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
  }
  vector<vector<int>> dp(2, vector<int>(req + 1));
  for (int x = 0; x <= req; x++) {
    dp[0][x] = (x % coins[0] == 0);
  }
  for (int c = 1, bit = 1; c < n; c++, bit = 1 - bit) {
    fill(dp[bit].begin(), dp[bit].end(), 0);
    dp[bit][0] = 1;
    for (int x = 1; x <= req; x++) {
      dp[bit][x] = dp[1 - bit][x];
      if (x < coins[c]) continue;
      dp[bit][x] += dp[bit][x - coins[c]];
      dp[bit][x] %= kMod;
    }
  }
  cout << dp[(n - 1) % 2][req] << "\n";
}