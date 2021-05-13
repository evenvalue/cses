#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  struct movie {
    int start;
    int end;

    bool operator<(const movie &other) const {
      return end < other.end;
    }
  };

  int n;
  cin >> n;
  vector<movie> movies(n);
  for (movie &m : movies) {
    cin >> m.start >> m.end;
  }
  sort(movies.begin(), movies.end());
  int end = 0;
  int seen = 0;
  for (const movie &m : movies) {
    if (m.start < end) continue;
    seen++;
    end = m.end;
  }
  cout << seen << "\n";
}