// February 2019 note:
// This code uses new C++17 structured binding
// use this compiler setting "g++ -O2 -std=gnu++17 {cpp17file}"

#include <bits/stdc++.h>                         // C++ code for task 5
using namespace std;
// utilize the natural sort order of primitive data types in the tuple
typedef tuple<int, int, int> iii;
int main() {
  vector<iii> birthdays;
  birthdays.emplace_back(5, 24, -1980);          // reorder DD/MM/YYYY
  birthdays.emplace_back(5, 24, -1982);          // to MM, DD, and then
  birthdays.emplace_back(11, 13, -1983);         // use NEGATIVE YYYY
  sort(birthdays.begin(), birthdays.end());      // that's all :)
  for (auto &[mm, dd, yyyy] : birthdays)         // C++17 style
    printf("%d %d %d\n", dd, mm, -yyyy);
}
