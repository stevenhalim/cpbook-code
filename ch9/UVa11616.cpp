// Roman Numerals

#include <bits/stdc++.h>
using namespace std;

void AtoR(int A) {
  map<int, string> cvt({
    {1000,"M"}, {900,"CM"}, {500,"D"}, {400,"CD"}, {100,"C"}, {90,"XC"},
    {50,"L"}, {40,"XL"}, {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"} });
  for (auto i = cvt.rbegin(); i != cvt.rend(); i++)  // from large to small
    while (A >= i->first) {
      printf("%s", i->second.c_str());
      A -= i->first;
    }
  printf("\n");
}

void RtoA(string R) {
  unordered_map<char, int> RtoA({
    {'I',1}, {'V',5}, {'X',10}, {'L',50},
    {'C',100}, {'D',500}, {'M',1000} });
  int value = 0;
  for (int i = 0; R[i]; i++)
    if (R[i+1] && RtoA[R[i]] < RtoA[R[i+1]]) {     // check next char first
      value += RtoA[R[i+1]] - RtoA[R[i]];                  // by definition
      i++;                                                // skip this char
    }
    else
      value += RtoA[R[i]];
  printf("%d\n", value);
}

int main() {
  AtoR(2018);
  RtoA("MMXVIII");
  // UVa 11616 will be trivial with AtoR and RtoA methods above
  // char str[1000];
  // while (gets(str) != NULL) {
  //   if (isdigit(str[0])) AtoR(atoi(str));       // Arabic to Roman Numerals
  //   else                 RtoA(str);             // Roman to Arabic Numerals
  // }
  return 0;
}
