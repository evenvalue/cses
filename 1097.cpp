#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  vector<vector<pair<int64, int64>>> dp(n, vector<pair<int64, int64>>(n));
  for (int x = 0; x < n; x++) {
    dp[x][x].first = a[x];
    dp[x][x].second = 0;
  }
  for (int len = 2; len <= n; len++) {
    for (int l = 0, r = l + len - 1; l < n and r < n; l++, r++) {
      dp[l][r].first = max(dp[l + 1][r].second + a[l], dp[l][r - 1].second + a[r]);
      dp[l][r].second = min(dp[l + 1][r].first, dp[l][r - 1].first);
    }
  }
  cout << dp[0][n - 1].first << "\n";
}