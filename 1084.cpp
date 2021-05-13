#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int apps, hotel, range;
  cin >> apps >> hotel >> range;
  vector<int> desire(apps);
  vector<int> rooms(hotel);
  for (int &size : desire) {
    cin >> size;
  }
  for (int &room : rooms) {
    cin >> room;
  }
  sort(desire.begin(), desire.end());
  sort(rooms.begin(), rooms.end());
  int ans = 0;
  for (int i = 0, j = 0; j < hotel and i < apps;) {
    if(rooms[j] < desire[i] - range) {
      j++;
    } else if (rooms[j] > desire[i] + range) {
      i++;
    } else {
      ans++;
      i++, j++;
    }
  }
  cout << ans << "\n";
}