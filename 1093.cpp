#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n;
  cin >> n;
  const int kSum = n * (n + 1) / 2;
  vector<vector<int>> dp(kSum / 2 + 1, vector<int>(n));
  dp[0][0] = 1;
  for (int req = 0; req <= kSum / 2; req++) {
    for (int x = 1; x < n; x++) {
      dp[req][x] = dp[req][x - 1];
      if (x > req) continue;
      dp[req][x] += dp[req - x][x - 1];
      dp[req][x] %= kMod;
    }
  }
  cout << (kSum % 2 == 0 ? dp[kSum / 2][n - 1] : 0) << "\n";
}