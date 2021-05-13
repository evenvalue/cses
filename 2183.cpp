#include <iostream>
#include <vector>
#include <algorithm>
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
  int64 ans = 1;
  for (int i = 0; i < n and a[i] <= ans; i++) {
    ans += a[i];
  }
  cout << ans << "\n";
}