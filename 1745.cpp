#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  int max_sum = 0;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
    max_sum += coin;
  }
  vector<vector<bool>> dp(max_sum + 1, vector<bool>(n + 1, false));
  dp[0][0] = true;
  for (int x = 0; x <= max_sum; x++) {
    for (int c = 1; c <= n; c++) {
      dp[x][c] = dp[x][c - 1];
      if (x < coins[c - 1]) continue;
      dp[x][c] = dp[x][c] or dp[x - coins[c - 1]][c - 1];
    }
  }
  int ans = 0;
  for (int sum = 1; sum <= max_sum; sum++) {
    ans += (dp[sum][n]);
  }
  cout << ans << "\n";
  for (int sum = 1; sum <= max_sum; sum++) {
    if (not dp[sum][n]) continue;
    cout << sum << " ";
  }
}