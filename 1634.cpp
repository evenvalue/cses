#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int inf = 1e9 + 10;
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
  }
  vector<int> ans(2e6 + 5, inf);
  ans[0] = 0;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < n; j++) {
      int &that = ans[i + coins[j]];
      that = min(that, ans[i] + 1);
    }
  }
  cout << (ans[x] == inf ? -1 : ans[x]) << "\n";
}