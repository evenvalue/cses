#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> dp(n + 1, 1e9 + 10);
  dp[0] = 0;
  for (int x = 1; x <= n; x++) {
    const string s = to_string(x);
    for (const char c : s) {
      dp[x] = min(dp[x], dp[x - (c - '0')] + 1);
    }
  }
  cout << dp[n] << "\n";
}