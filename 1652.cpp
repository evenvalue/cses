#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<vector<int>> dp(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      cin >> c;
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + (c == '*');
    }
  }
  while (q--) {
    int h1, w1, h2, w2;
    cin >> h1 >> w1 >> h2 >> w2;
    cout << dp[h2][w2] - dp[h1 - 1][w2] - dp[h2][w1 - 1] + dp[h1 - 1][w1 - 1] << "\n";
  }
}