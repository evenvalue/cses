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
  int64 ans = 0;
  for (int i = 1; i < n; i++) {
    const int inc = max(0, a[i - 1] - a[i]);
    a[i] += inc;
    ans += inc;
  }
  cout << ans << "\n";
}