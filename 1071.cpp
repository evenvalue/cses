#include <iostream>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int64 x, y;
    cin >> x >> y;
    if (x < y) {
      if (y & 1) {
        cout << y * y - x + 1LL;
      } else {
        cout << (y - 1) * (y - 1) + x;
      }
    } else {
      if (not(x & 1)) {
        cout << x * x - y + 1LL;
      } else {
        cout << (x - 1) * (x - 1) + y;
      }
    }
    cout << '\n';
  }
}