#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

void solve() {
  string s;
  cin >> s;
  const int n = (int)s.size();
  vector<int> cnt(26);
  for (const char c : s) cnt[c - 'A']++;
  vector<int> odd;
  for (int alpha = 0; alpha < 26; alpha++) {
    if (cnt[alpha] & 1) odd.push_back(alpha);
  }
  if (odd.size() == (n & 1)) {
    string ans;
    if (n & 1) {
      for (int alpha = 0; alpha < 26; alpha++) {
        if (alpha == odd[0]) continue;
        for (int i = 0; i < cnt[alpha] / 2; i++) {
          ans += (char)(alpha + 'A');
        }
      }
      cout << ans;
      for (int i = 0; i < cnt[odd[0]]; i++) {
        cout << (char)(odd[0] + 'A');
      }
    } else {
      for (int alpha = 0; alpha < 26; alpha++) {
        for (int i = 0; i < cnt[alpha] / 2; i++) {
          ans += (char)(alpha + 'A');
        }
      }
      cout << ans;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
  } else {
    cout << "NO SOLUTION";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
    cout << '\n';
  }
}