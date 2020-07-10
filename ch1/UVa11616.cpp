// Roman Numerals

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, string> is;

void AtoR(int A) {                               // Arabic to Roman
  vector<is> convert({
    {1000,"M"}, {900,"CM"}, {500,"D"}, {400,"CD"}, {100,"C"}, {90,"XC"},
    {50,"L"}, {40,"XL"}, {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}
  });
  for (auto &[value, roman] : convert)           // from large to small
    while (A >= value) {
      cout << roman;
      A -= value;
    }
  cout << "\n";
}

int value(char letter) {
  switch (letter) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
  }
  return 0;
}

void RtoA(string R) {                            // Roman to Arabic
  int ans = 0;
  for (int i = 0; R[i]; ++i)
    if (R[i+1] && (value(R[i]) < value(R[i+1]))) { // check next char first
      ans += value(R[i+1])-value(R[i]);          // by definition
      ++i;                                       // skip this char
    }
    else
      ans += value(R[i]);
  cout << ans << "\n";
}

int main() {
  string S;
  while (getline(cin, S)) {
    if (isdigit(S[0]))
      AtoR(stoi(S));                             // Arabic to Roman Numerals
    else
      RtoA(S);                                   // Roman to Arabic Numerals
  }
  return 0;
}
