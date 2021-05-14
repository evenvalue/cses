#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  set<int> lights = {0, n};
  multiset<int> diff = {n};
  while (m--) {
    int new_light;
    cin >> new_light;
    auto it = lights.insert(new_light).first;
    diff.erase(diff.find(*next(it) - *prev(it)));
    diff.insert(*it - *prev(it));
    diff.insert(*next(it) - *it);
    cout << *(prev(diff.end())) << " ";
  }
}