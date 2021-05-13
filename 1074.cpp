#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  sort(a.begin(), a.end());
  const int kMid = a[n / 2];
  int64 ans = 0;
  for (int i = 0; i < n; i++) {
    ans += abs(a[i] - kMid);
  }
  cout << ans << "\n";
}