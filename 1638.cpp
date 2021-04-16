#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n;
  cin >> n;
  vector<vector<int>> dp(2, vector<int>(n));
  string row;
  cin >> row;
  dp[0][0] = (row[0] == '.');
  for (int c = 1; c < n; c++) {
    dp[0][c] = (row[c] == '.') * dp[0][c - 1];
  }
  for (int r = 1, bit = 1; r < n; r++, bit = 1 - bit) {
    cin >> row;
    dp[bit][0] = (row[0] == '.') * dp[1 - bit][0];
    for (int c = 1; c < n; c++) {
      if (row[c] == '.') {
        dp[bit][c] = (dp[1 - bit][c] + dp[bit][c - 1]) % kMod;
      } else {
        dp[bit][c] = 0;
      }
    }
  }
  cout << dp[(n - 1) % 2][n - 1] << "\n";
}