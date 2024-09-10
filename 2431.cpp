#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int kInf = 1e18;

int32_t main() {
  vector<int> count = {0};
  for (int i = 1, num = 9; count.back() <= kInf; i++, num *= 10) {
    count.push_back(count.back() + i * num);
  }

  vector<int> power = {0, 1};
  while (power.size() < count.size()) {
    power.push_back(power.back() * 10);
  }

  auto digits = [&](const int x) {
    auto s = to_string(x);
    const int n = s.size();
    return count[n - 1] + (x - power[n] + 1) * n;
  };

  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;

    int lo = 1, hi = power.back() * 10;
    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      if (digits(mid) < x) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    const int i = x - digits(lo - 1);
    cout << to_string(lo)[i - 1] << '\n';
  }
}
