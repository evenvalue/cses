#include <iostream>
#include <queue>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  queue<int> q;
  for (int x = 1; x <= n; x++) {
    q.push(x);
  }
  bool push = true;
  while (not q.empty()) {
    const int x = q.front();
    if (push) {
      q.push(x);
    } else {
      cout << x << " ";
    }
    q.pop();
    push = not push;
  }
}