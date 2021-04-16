#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int mod = 1e9 + 7;
  int n;
  cin >> n;
  vector<int> ways(n + 6);
  ways[0] = 1;
  for (int i = 0; i < n; i++) {
    for (const int x : {1, 2, 3, 4, 5, 6}) {
      ways[i + x] += ways[i];
      ways[i + x] %= mod;
    }
  }
  cout << ways[n] << "\n";
}