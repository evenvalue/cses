#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  struct project {
    int s = 0, e = 0;
    int reward = 0;
  };

  int n;
  cin >> n;
  vector<project> projects(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> projects[i].s >> projects[i].e >> projects[i].reward;
  }
  sort(projects.begin() + 1, projects.end(), [](const project &p1, const project &p2) {
    return p1.e < p2.e;
  });
  vector<int> last(n + 1);
  for (int i = 1; i <= n; i++) {
    last[i] = projects[i].e;
  }
  vector<int64> best(n + 1);
  for (int i = 1; i <= n; i++) {
    const int j = (int)distance(last.begin(), lower_bound(last.begin(), last.end(), projects[i].s)) - 1;
    best[i] = max(best[i - 1], best[j] + projects[i].reward);
  }
  cout << best[n] << "\n";
}