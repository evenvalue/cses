#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  const int log = 30;
  vector<vector<int>> st(n, vector<int>(log + 1));
  for (int x = 0; x < n; x++) {
    cin >> st[x][0];
    st[x][0]--;
  }
  for (int j = 1; j <= log; j++) {
    for (int x = 0; x < n; x++) {
      const int anc = st[x][j - 1];
      st[x][j] = st[anc][j - 1];
    }
  }
  while (q--) {
    int x, k;
    cin >> x >> k;
    x--;
    for (int j = log; j >= 0; j--) {
      if ((1 << j) > k) continue;
      k -= (1 << j);
      x = st[x][j];
    }
    cout << x + 1 << '\n';
  }
}