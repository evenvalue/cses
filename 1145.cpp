#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kInf = 1e9 + 10;

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  vector<int> dp(n + 1, kInf);
  dp[0] = 0;
  for (int &x : a) {
    const int replace = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), x));
    dp[replace] = x;
  }
  cout << distance(dp.begin(), lower_bound(dp.begin(), dp.end(), kInf)) - 1 << "\n";
}