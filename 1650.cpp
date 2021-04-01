#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<int64> pref(n + 1);
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    pref[i] = pref[i - 1] ^ x;
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << (pref[r] ^ pref[l - 1]) << "\n";
  }
}