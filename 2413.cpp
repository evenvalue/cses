#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9 + 7;
  const int N = 1e6 + 5;

  vector<vector<int64>> dp(N, vector<int64>(2));
  dp[1][0] = dp[1][1] = 1;
  for (int h = 2; h < N; h++) {
    (dp[h][0] = 4 * dp[h - 1][0] + dp[h - 1][1]) %= mod;
    (dp[h][1] = 2 * dp[h - 1][1] + dp[h - 1][0]) %= mod;
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << (dp[n][0] + dp[n][1]) % mod << "\n";
  }
}