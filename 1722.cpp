#include <iostream>
#include <vector>
using namespace std;

#define int64 int64_t

const int kMod = 1e9 + 7;

struct matrix {
  int n;
  vector<vector<int>> a;

  explicit matrix(const int n) : n(n), a(n, vector<int>(n)) {}

  matrix operator*(const matrix &other) const {
    matrix ret(n);
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

matrix binpow(matrix &m, int64 pow) {
  matrix product(2);
  product.a = {{1, 0}, {0, 1}};
  while (pow) {
    if (pow & 1) {
      product = product * m;
    }
    m = m * m;
    pow /= 2;
  }
  return product;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int64 n;
  cin >> n;
  matrix m(2);
  m.a = {{0, 1}, {1, 1,}};
  cout << binpow(m, n).a[1][0] << "\n";
}
