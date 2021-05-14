#include <iostream>
#include <iterator>
#include <set>
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
    auto lamp = lights.insert(new_light).first;
    diff.erase(diff.find(*next(lamp) - *prev(lamp)));
    diff.insert(*lamp - *prev(lamp));
    diff.insert(*next(lamp) - *lamp);
    cout << *(prev(diff.end())) << " ";
  }
}