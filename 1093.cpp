#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;

  int n;
  cin >> n;
  const int kSum = n * (n + 1) / 2;
  vector<vector<int>> ways(kSum / 2 + 1, vector<int>(n));
  fill(ways[0].begin(), ways[0].end(), 1);
  for (int req = 1; req <= kSum / 2; req++) {
    for (int x = 1; x < n; x++) {
      ways[req][x] = ways[req][x - 1];
      if (x > req) continue;
      ways[req][x] += ways[req - x][x - 1];
      ways[req][x] %= kMod;
    }
  }
  cout << (kSum % 2 == 0 ? ways[kSum / 2][n - 1] : 0) << "\n";
}