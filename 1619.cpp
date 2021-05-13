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
  vector<pair<int, bool>> a(2 * n);
  for (int i = 0; i < n; i++) {
    int in, out;
    cin >> in >> out;
    a[2 * i] = {in, true};
    a[2 * i + 1] = {out, false};
  }
  sort(a.begin(), a.end());
  int cur = 0, ans = 0;
  for (int i = 0; i < 2 * n; i++) {
    cur += (a[i].second ? 1 : -1);
    ans = max(ans, cur);
  }
  cout << ans << "\n";
}