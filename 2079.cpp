#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
  vector<int> size(n, 1);
  function<int(int, int)> calc_size = [&](const int x, const int p) {
    for (const int y : g[x]) {
      if (y == p) continue;
      size[x] += calc_size(y, x);
    }
    return size[x];
  };
  calc_size(0, -1);
  function<int(int, int)> find_centroid = [&](const int x, const int p) {
    int centroid = x;
    for (const int y : g[x]) {
      if (y == p) continue;
      if (n / 2 < size[y]) {
        centroid = find_centroid(y, x);
      }
    }
    return centroid;
  };
  cout << find_centroid(0, -1) + 1 << "\n";
}