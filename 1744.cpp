#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> cuts(n + 1, vector<int>(m + 1, 1e9 + 10));
  for (int side = 0; side <= min(n, m); side++) {
    cuts[side][side] = 0;
  }
  for (int r = 0; r <= n; r++) {
    for (int c = 0; c <= m; c++) {
      for (int vcut = 0; vcut < c; vcut++) {
        cuts[r][c] = min(cuts[r][c], cuts[r][vcut] + cuts[r][c - vcut] + 1);
      }
      for (int hcut = 0; hcut < r; hcut++) {
        cuts[r][c] = min(cuts[r][c], cuts[hcut][c] + cuts[r - hcut][c] + 1);
      }
    }
  }
  cout << cuts[n][m] << "\n";
}