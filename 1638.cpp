#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9 + 7;

  int n;
  cin >> n;
  vector<vector<int>> dp(n, vector<int>(n, 0));
  dp[0][0] = 1;
  for (int r = 0; r < n; r++) {
    string row;
    cin >> row;
    for (int c = 0; c < n; c++) {
      if (row[c] == '.') {
        if (0 < r) {
          (dp[r][c] += dp[r - 1][c]) %= mod;
        }
        if (0 < c) {
          (dp[r][c] += dp[r][c - 1]) %= mod;
        }
      } else {
        dp[r][c] = 0;
      }
    }
  }
  cout << dp[n - 1][n - 1] << "\n";
}