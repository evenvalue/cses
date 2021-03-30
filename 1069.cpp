#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string s;
  cin >> s;
  char cur = ' ';
  int maxcnt = 0, cnt = 0;
  for (char c : s) {
    if (c == cur) {
      cnt++;
    } else {
      cur = c;
      cnt = 1;
    }
    maxcnt = max(maxcnt, cnt);
  }
  cout << maxcnt << "\n";
}