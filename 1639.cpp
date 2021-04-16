#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string a, b;
  cin >> a >> b;
  const int n = a.size();
  const int m = b.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i < n; i++) {
    dp[i][m] = n - i;
  }
  for (int j = 0; j < m; j++) {
    dp[n][j] = m - j;
  }
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      int ans;
      if (a[i] == b[j]) {
        ans = dp[i + 1][j + 1];
      } else {
        ans = 1 + min({dp[i][j + 1], dp[i + 1][j], dp[i + 1][j + 1]});
      }
      dp[i][j] = ans;
    }
  }
  cout << dp[0][0] << "\n";
}