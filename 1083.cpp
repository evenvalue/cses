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
  vector<int> a(n - 1);
  for (int &x : a) {
    cin >> x;
  }
  sort(a.begin(), a.end());
  for (int i = 1; i <= n; i++) {
    if (i != a[i - 1]) {
      cout << i << "\n";
      return 0;
    }
  }
}