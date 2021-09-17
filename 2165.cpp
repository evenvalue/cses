#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n'
using int64 = int64_t;

const int64 kInfL = 1e15 + 10;
const int kInf = 1e9 + 10;
const int kMod = 1e9 + 7;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<pair<int, int>> steps;

void toh(const int n, const int s1, const int s2, const int s3) { //tower of hanoi
  if (n == 0) return;
  toh(n - 1, s1, s3, s2);
  steps.emplace_back(s1, s3);
  toh(n - 1, s2, s1, s3);
}

void solve(const int TestCase) {
  int n;
  cin >> n;
  steps.reserve((1 << n) - 1);
  toh(n, 1, 2, 3);
  cout << steps.size() << '\n';
  for (const auto [from, to] : steps) {
    cout << from << ' ' << to << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  auto begin = std::chrono::high_resolution_clock::now();

  int t = 1;
  //cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    solve(tc);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
}