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
  vector<int> ans(x + 1, kInf);
  ans[0] = 0;
  for (int i = 0; i < x; i++) {
    for (const int coin : coins) {
      if (i + coin > x) continue;
      ans[i + coin] = min(ans[i + coin], ans[i] + 1);
    }
  }
  cout << (ans[x] == kInf ? -1 : ans[x]) << "\n";
}