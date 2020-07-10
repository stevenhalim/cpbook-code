// Roman Numerals, 0.986s in Java (almost TLE), only 0.032s in C++

import java.util.*;
import java.io.*;

class Main {
  private static PrintWriter pw;

  private static void AtoR(int A) {
    // process from larger values to smaller values
    TreeMap<Integer, String> cvt = new TreeMap<Integer, String>(Collections.reverseOrder());
    cvt.put(1000, "M"); cvt.put(900, "CM"); cvt.put(500, "D"); cvt.put(400, "CD");
    cvt.put(100,  "C"); cvt.put(90,  "XC"); cvt.put(50,  "L"); cvt.put(40,  "XL");
    cvt.put(10,   "X"); cvt.put(9,   "IX"); cvt.put(5,   "V"); cvt.put(4,   "IV");
    cvt.put(1,    "I");

    Set keys = cvt.keySet();
    for (Iterator i = keys.iterator(); i.hasNext();) {
      Integer key = (Integer) i.next();
      String value = (String) cvt.get(key);
      while (A >= key) {
        pw.print(value);
        A -= key;
      }
    }
    pw.printf("\n");
  }

  private static int value(char letter) {
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

  private static void RtoA(String R) {
    int ans = 0;
    for (int i = 0; i < R.length(); ++i)
      if ((i+1 < R.length()) && value(R.charAt(i)) < value(R.charAt(i+1))) { // check next char first
        ans += value(R.charAt(i+1))-value(R.charAt(i)); // by definition
        ++i;                                     // skip this char
      }
      else
        ans += value(R.charAt(i));
    pw.printf("%d\n", ans);
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    while (true) {
      String str = br.readLine();
      if (str == null) break;
      if (Character.isDigit(str.charAt(0))) AtoR(Integer.parseInt(str)); // Arabic to Roman Numerals
      else                                  RtoA(str); // Roman to Arabic Numerals
    }

    pw.close();
  }
}
