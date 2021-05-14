#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const int kInf = 1e9 + 10;

  int n;
  cin >> n;
  vector<int> tower(n + 1, kInf);
  while (n--) {
    int x;
    cin >> x;
    const int pile = distance(tower.begin(), upper_bound(tower.begin(), tower.end(), x));
    tower[pile] = x;
  }
  cout << distance(tower.begin(), lower_bound(tower.begin(), tower.end(), kInf));
}