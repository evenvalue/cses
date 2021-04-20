#include <iostream>
#include <vector>
using namespace std;

void update(int &r1, int &l1, const int r2, const int l2) {
  if (r1 < r2) return;
  if (r1 > r2) {
    r1 = r2;
    l1 = l2;
  } else {
    l1 = min(l1, l2);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, x;
  cin >> n >> x;
  vector<int> weights(n);
  for (int &weight : weights) {
    cin >> weight;
  }
  const int N = 1 << n;
  vector<int> ride(N, n + 1);
  vector<int> last(N);
  ride[0] = 1;
  for (int mask = 1; mask < N; mask++) {
    for (int p = 0; p < n; p++) {
      if ((mask & (1 << p)) == 0) continue;
      const int option = mask ^ (1 << p);
      if (last[option] + weights[p] <= x) {
        update(ride[mask], last[mask], ride[option], last[option] + weights[p]);
      } else {
        update(ride[mask], last[mask], ride[option] + 1, weights[p]);
      }
    }
  }
  cout << ride[N - 1] << "\n";
}