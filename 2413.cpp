#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kMod = 1e9 + 7;
  const int kMaxN = 1e6;

  vector<int64> chop(kMaxN + 1);
  vector<int64> join(kMaxN + 1);
  chop[1] = join[1] = 1;
  for (int h = 2; h <= kMaxN; h++) {
    chop[h] = (4 * chop[h - 1] + join[h - 1]) % kMod;
    join[h] = (2 * join[h - 1] + chop[h - 1]) % kMod;
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << (chop[n] + join[n]) % kMod << "\n";
  }
}