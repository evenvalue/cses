#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

const int kMod = 1e9 + 7;

template<int n>
struct matrix {
  vector<vector<int>> a;

  explicit matrix() : a(n, vector<int>(n)) {}

  matrix operator*(const matrix &other) const {
    matrix ret;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ret.a[i][k] = (ret.a[i][k] + ((int64) a[i][j] * other.a[j][k])) % kMod;
        }
      }
    }
    return ret;
  }
};

template<int n>
matrix<n> binpow(matrix<n> m, int64 exp) {
  matrix<n> product;
  for (int i = 0; i < n; i++) {
    product.a[i][i] = 1;
  }
  while (exp) {
    if (exp & 1) {
      product = product * m;
    }
    m = m * m;
    exp /= 2;
  }
  return product;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int64 n;
  cin >> n;
  matrix<2> m;
  m.a = {{0, 1}, {1, 1}};
  cout << binpow<2>(m, n).a[1][0] << "\n";
}
