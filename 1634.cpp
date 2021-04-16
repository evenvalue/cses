#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kInf = 1e9 + 10;

  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
  }
  vector<int> dp(x + 1, kInf);
  dp[0] = 0;
  for (int i = 0; i < x; i++) {
    for (const int coin : coins) {
      if (i + coin > x) continue;
      dp[i + coin] = min(dp[i + coin], dp[i] + 1);
    }
  }
  cout << (dp[x] == kInf ? -1 : dp[x]) << "\n";
}