#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, budget;
  cin >> n >> budget;
  vector<int> cost(n), page(n);
  for (int &price : cost) {
    cin >> price;
  }
  for (int &book : page) {
    cin >> book;
  }
  vector<vector<int>> dp(n + 1, vector<int>(budget + 1));
  for (int b = 1; b <= n; b++) {
    for (int x = 1; x <= budget; x++) {
      dp[b][x] = dp[b - 1][x];
      if (x < cost[b - 1]) continue;
      dp[b][x] = max(dp[b][x], dp[b - 1][x - cost[b - 1]] + page[b - 1]);
    }
  }
  cout << dp[n][budget] << "\n";
}