#include <bits/stdc++.h>
using namespace std;

int main() {
  int arr[5] = {7,7,7};   // initial size (5) and initial value {7,7,7,0,0}
  vector<int> v(5, 5);    // initial size (5) and initial value {5,5,5,5,5}

  printf("arr[2] = %d and v[2] = %d\n", arr[2], v[2]);           // 7 and 5

  for (int i = 0; i < 5; i++) {
    arr[i] = i;
    v[i] = i;
  }

  printf("arr[2] = %d and v[2] = %d\n", arr[2], v[2]);           // 2 and 2

  // arr[5] = 5;     // static array will generate index out of bound error
  // uncomment the line above to see the error

  v.push_back(5);                          // but vector will resize itself
  printf("v[5] = %d\n", v[5]);                                         // 5
  
  return 0;
}
