#include <bits/stdc++.h>                         // C++ code for task 5
using namespace std;
typedef tuple<int, int, int> iii;                // use natural order
int main() {
  multiset<iii> birthdays;                       // auto sorting :)
  birthdays.emplace(5, 24, -1980);               // reorder DD/MM/YYYY
  birthdays.emplace(5, 24, -1982);               // to MM, DD, and then
  birthdays.emplace(11, 13, -1983);              // use NEGATIVE YYYY
  birthdays.emplace(5, 24, -1982);               // duplicates allowed
  for (auto &[mm, dd, yyyy] : birthdays)         // C++17 style
    printf("%d %d %d\n", dd, mm, -yyyy);
}
