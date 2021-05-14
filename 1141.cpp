#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int convert(vector<int> &a) {
  set<int> s;
  for (const int &x : a) {
    s.insert(x);
  }
  vector<int> e;
  e.reserve(s.size());
  for (const int x : s) {
    e.push_back(x);
  }
  for (int &x : a) {
    x = distance(e.begin(), lower_bound(e.begin(), e.end(), x));
  }
  return s.size();
}

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
  vector<int> occ(convert(a), -1);
  int ans = 0, len = 0;
  for (int i = 0; i < n; i++) {
    if (occ[a[i]] != -1 and occ[a[i]] >= i - len) {
      len = i - occ[a[i]] - 1;
    }
    len++;
    ans = max(ans, len);
    occ[a[i]] = i;
  }
  cout << ans << "\n";
}