#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int check(const int y, const vector<int> &occ) {
  return (occ[y] < occ[y - 1]) + (occ[y + 1] < occ[y]);
}

int adj(int x, int y, const vector<int> &occ) {
  if (x < y) swap(x, y);
  if (x - y == 1) {
    return (occ[x] < occ[y]);
  } else {
    return 0;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<int> num(n + 2);
  vector<int> occ(n + 2);
  num[n + 1] = occ[n + 1] = n + 1;
  for (int i = 1; i <= n; i++) {
    cin >> num[i];
    occ[num[i]] = i;
  }
  int rounds = 1;
  for (int i = 1; i <= n; i++) {
    rounds += (occ[i] < occ[i - 1]);
  }
  while (m--) {
    int x, y;
    cin >> x >> y;
    swap(num[x], num[y]);
    x = num[x], y = num[y];
    const int kBefore = check(x, occ) + check(y, occ) - adj(x, y, occ);
    swap(occ[x], occ[y]);
    const int kAfter = check(x, occ) + check(y, occ) - adj(x, y, occ);
    rounds += kAfter - kBefore;
    cout << rounds << "\n";
  }
}