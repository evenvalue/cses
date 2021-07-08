#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#define int64 int64_t
#define debug(x) cerr << #x << ": " << x << '\n'

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

vector<int> sieve(const int n) {
  vector<int> primes;
  primes.reserve(4203);
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (not is_prime[i]) continue;
    primes.push_back(i);
    for (int j = i * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }
  return primes;
}

int count_divisors(int x, const vector<int> &primes) {
  int ans = 1;
  for (const int p : primes) {
    if (p * p > x) break;
    int cnt = 0;
    while (x % p == 0) {
      cnt++;
      x /= p;
    }
    ans *= (cnt + 1);
  }
  ans *= (x > 1 ? 2 : 1);
  return ans;
}

void solve(const vector<int> &primes) {
  int n;
  cin >> n;
  cout << count_divisors(n, primes);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  const vector<int> primes = sieve(4e4);

  int t = 1;
  cin >> t;
  while (t--) {
    solve(primes);
    cout << '\n';
  }
}