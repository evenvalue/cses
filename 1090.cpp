#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, capacity;
  cin >> n >> capacity;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  sort(a.begin(), a.end());
  int ans = 0;
  for (int i = 0, j = n - 1; i <= j;) {
    ans++;
    if (i == j) {
      break;
    } else if (a[i] + a[j] <= capacity) {
      i++, j--;
    } else {
      j--;
    }
  }
  cout << ans << "\n";
}