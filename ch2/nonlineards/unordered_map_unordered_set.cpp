#include <bits/stdc++.h>
using namespace std;

int main() {
  // note, we don't have to use .clear() if we have just initialized the set/map
  unordered_set<int> used_values; // used_values.clear();
  unordered_map<string, int> mapper; // mapper.clear();

  // suppose we enter these 7 name-score pairs below
  /*
  john 78
  billy 69
  andy 80
  steven 77
  felix 82
  grace 75
  martin 81
  */
  mapper["john"]   = 78; used_values.insert(78);
  mapper["billy"]  = 69; used_values.insert(69);
  mapper["andy"]   = 80; used_values.insert(80);
  mapper["steven"] = 77; used_values.insert(77);
  mapper["felix"]  = 82; used_values.insert(82);
  mapper["grace"]  = 75; used_values.insert(75);
  mapper["martin"] = 81; used_values.insert(81);

  // then the internal content of mapper/used_values are not really known
  // (implementation dependent)

  // iterating through the content of mapper will give a jumbled output
  // as the keys are hashed into various slots
  for (auto &[key, value] : mapper)              // C++17 style
    printf("%s %d\n", key.c_str(), value);

  // map can also be used like this
  printf("steven's score is %d, grace's score is %d\n",
    mapper["steven"], mapper["grace"]);
  printf("==================\n");

  // there is no lower_bound and upper_bound in an unordered_map

  // O(1) search, found
  printf("%d\n", *used_values.find(77));
  // O(1) search, not found
  if (used_values.find(79) == used_values.end())
    printf("79 not found\n");

  return 0;
}
