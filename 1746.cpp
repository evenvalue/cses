#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n, m;
  cin >> n >> m;
  vector<vector<int>> dp(n, vector<int>(m + 1));
  int x;
  cin >> x;
  if (x == 0) {
    fill(dp[0].begin(), dp[0].end(), 1);
  } else {
    dp[0][x] = 1;
  }
  for (int i = 1; i < n; i++) {
    cin >> x;
    if (x == 0) {
      for (int j = 1; j <= m; j++) {
        for (int k : {j - 1, j, j + 1}) {
          if (1 <= k and k <= m) {
            dp[i][j] += dp[i - 1][k];
            dp[i][j] %= kMod;
          }
        }
      }
    } else {
      for (int k : {x - 1, x, x + 1}) {
        if (1 <= k and k <= m) {
          dp[i][x] += dp[i - 1][k];
          dp[i][x] %= kMod;
        }
      }
    }
  }
  int ans = 0;
  for (int j = 1; j <= m; j++) {
    (ans += dp[n - 1][j]) %= kMod;
  }
  cout << ans << "\n";
}