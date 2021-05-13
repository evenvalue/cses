#include <vector>
#include <iostream>
using namespace std;

#define int64 int64_t

int64 kadane(const vector<int> &a) {
  const int n = a.size();
  int64 mx = a[0], cur = a[0];
  for (int i = 1; i < n; i++) {
    cur = max(cur + a[i], (int64)a[i]);
    mx = max(mx, cur);
  }
  return mx;
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
  cout << kadane(a) << "\n";
}