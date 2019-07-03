#include <bits/stdc++.h>
using namespace std;

int main() {
  int arr[5] = {7,7,7}; // initial size (5) and initial value {7,7,7,0,0}
  vector<int> v(5, 5); // initial size (5) and initial value {5,5,5,5,5}

  printf("arr[2] = %d and v[2] = %d\n", arr[2], v[2]); // 7 and 5

  iota(arr, arr+5, 0);                           // arr = {0,1,2,3,4}
  iota(v.begin(), v.end(), 7);                   // v = {7,8,9,10,11}

  printf("arr[2] = %d and v[2] = %d\n", arr[2], v[2]); // 2 and 9

  // arr[5] = 5;                                 // undefined behavior
  // printf("arr[5] = %d\n", arr[5]);            // RTE
  // uncomment the line above to see the error (perhaps use -Wall compilation flag)

  v.push_back(77);                               // vector resizes itself
  printf("v[5] = %d\n", v[5]);                   // 77
  
  return 0;
}
