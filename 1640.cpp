#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, sum;
  cin >> n >> sum;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(a.begin(), a.end());
  for (int l = 0, r = n - 1; l < r;) {
    if (a[l].first + a[r].first< sum) {
      l++;
    } else if (a[l].first + a[r].first > sum) {
      r--;
    } else {
      cout << a[l].second + 1 << " " << a[r].second + 1 << "\n";
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
}