#include <iostream>
#include <vector>
using namespace std;

class TreeAnc {
  vector<vector<int>> st;
  int log;

public:
  explicit TreeAnc(const int n, const vector<int> &p) {
    log = 0;
    while (1 << log <= n) {
      log++;
    }
    st.assign(n, vector<int>(log + 1));
    for (int i = 0; i < n; i++) {
      st[i][0] = p[i];
    }
    for (int j = 1; j <= log; j++) {
      for (int i = 0; i < n; i++) {
        const int anc = st[i][j - 1];
        st[i][j] = anc == -1 ? -1 : st[anc][j - 1];
      }
    }
  }

  int get_anc(int x, const int up) {
    if (1 << log < up) return -1;
    for (int j = 0; j <= log; j++) {
      if (x == -1) return -1;
      if (up & (1 << j)) {
        x = st[x][j];
      }
    }
    return x;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<int> p(n, -1);
  for (int x = 1; x < n; x++) {
    cin >> p[x];
    p[x]--;
  }
  TreeAnc t(n, p);
  while (q--) {
    int x, k;
    cin >> x >> k;
    int ans = t.get_anc(x - 1, k);
    cout << (ans == -1 ? -1 : ans + 1) << "\n";
  }
}