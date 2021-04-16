#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
  }
  vector<int> dp(x + 1);
  dp[0] = 1;
  for (int i = 0; i < x; i++) {
    for (const int coin : coins) {
      if (i + coin > x) continue;
      dp[i + coin] += dp[i];
      dp[i + coin] %= kMod;
    }
  }
  cout << dp[x] << "\n";
}