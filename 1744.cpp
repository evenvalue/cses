#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  for (int r = 0; r <= n; r++) {
    for (int c = 0; c <= m; c++) {
      if (r == c) continue;
      dp[r][c] = 1e9 + 10;
      for (int vcut = 0; vcut < c; vcut++) {
        dp[r][c] = min(dp[r][c], dp[r][vcut] + dp[r][c - vcut] + 1);
      }
      for (int hcut = 0; hcut < r; hcut++) {
        dp[r][c] = min(dp[r][c], dp[hcut][c] + dp[r - hcut][c] + 1);
      }
    }
  }
  cout << dp[n][m] << "\n";
}