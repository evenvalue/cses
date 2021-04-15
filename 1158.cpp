#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, money;
  cin >> n >> money;
  vector<int> cost(n), page(n);
  for (int &price : cost) {
    cin >> price;
  }
  for (int &book : page) {
    cin >> book;
  }
  vector<vector<int>> dp(n + 1, vector<int>(money + 1));
  for (int b = 1; b <= n; b++) {
    for (int x = 1; x <= money; x++) {
      dp[b][x] = dp[b - 1][x];
      const int prev = x - cost[b - 1];
      if (prev < 0) continue;
      dp[b][x] = max(dp[b][x], dp[b - 1][prev] + page[b - 1]);
    }
  }
  cout << dp[n][money] << "\n";
}