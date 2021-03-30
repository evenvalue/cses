#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9 + 7;
  int n;
  cin >> n;
  vector<int64> ways(n + 6);
  ways[0] = 1;
  for (int i = 0; i < n; i++) {
    const int me = ways[i];
    ways[i + 1] = (ways[i + 1] + me) % mod;
    ways[i + 2] = (ways[i + 2] + me) % mod;
    ways[i + 3] = (ways[i + 3] + me) % mod;
    ways[i + 4] = (ways[i + 4] + me) % mod;
    ways[i + 5] = (ways[i + 5] + me) % mod;
    ways[i + 6] = (ways[i + 6] + me) % mod;
  }
  cout << ways[n] << "\n";
}