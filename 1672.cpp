#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;
  vector<vector<long long>> d(n, vector<long long>(n, 1e15));
  while (m--) {
    int x, y, w;
    cin >> x >> y >> w;
    d[x - 1][y - 1] = min(d[x - 1][y - 1], 1LL * w);
    d[y - 1][x - 1] = d[x - 1][y - 1];
  }
  for (int i = 0; i < n; i++) {
    d[i][i] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << (d[x - 1][y - 1] != 1e15 ? d[x - 1][y - 1] : -1) << "\n";
  }
}