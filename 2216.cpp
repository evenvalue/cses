#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a[x - 1] = i;
  }
  int ans = 1;
  for (int i = 1; i < n; i++) {
    ans += (a[i] < a[i - 1]);
  }
  cout << ans << "\n";
}