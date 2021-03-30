#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9 + 7;
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
  }
  vector<int64> ans(2e6 + 5);
  ans[0] = 1;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < n; j++) {
      int64 &that = ans[i + coins[j]];
      that = that + ans[i];
      that %= mod;
    }
  }
  cout << ans[x] << "\n";
}