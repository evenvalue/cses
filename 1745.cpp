#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  int max_sum = 0;
  vector<int> coins(n);
  for (int &coin : coins) {
    cin >> coin;
    max_sum += coin;
  }
  vector<bool> can(max_sum + 1, false);
  can[0] = true;
  for (const int coin : coins) {
    for (int i = max_sum; i >= coin; i--) {
      can[i] = can[i] or can[i - coin];
    }
  }
  cout << count(can.begin(), can.end(), true) - 1 << "\n";
  for (int i = 1; i <= max_sum; i++) {
    if (not can[i]) continue;
    cout << i << " ";
  }
}