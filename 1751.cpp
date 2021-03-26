#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> to(n);
  for (int &x : to) {
    cin >> x;
    x--;
  }
  vector<int> ans(n, 0);
  vector<bool> visit(n, false);
  auto solve = [&](int x) {
    int y = x;
    int len = 0;
    while (not visit[y]) {
      visit[y] = true;
      len++;
      y = to[y];
    }
    while (x != y) {
      ans[x] = ans[y] + len;
      x = to[x];
      len--;
    }
    if (len == 0) return;
    ans[y] = len;
    x = to[y];
    while (x != y) {
      ans[x] = len;
      x = to[x];
    }
  };
  for (int i = 0; i < n; i++) {
    if (not visit[i]) {
      solve(i);
    }
  }
  for (const int x : ans) {
    cout << x << " ";
  }
  cout << "\n";
}