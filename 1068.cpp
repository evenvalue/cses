#include <iostream>
using namespace std;

using int64 = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int64 n;
  cin >> n;
  while (n != 1) {
    cout << n << ' ';
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n *= 3;
      n++;
    }
  }
  cout << 1 << '\n';
}