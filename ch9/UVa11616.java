// Roman Numerals, 0.986s in Java (almost TLE), only 0.032s in C++

import java.util.*;
import java.io.*;

class Main {
  public static PrintWriter pr;

  public static void AtoR(int A) {
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
        pr.print(value);
        A -= key;
      }
    }
    pr.printf("\n");
  }

  public static void RtoA(String R) {
    TreeMap<Character, Integer> RtoA = new TreeMap<Character, Integer>();
    RtoA.put('I', 1);   RtoA.put('V', 5);   RtoA.put('X', 10);   RtoA.put('L', 50);
    RtoA.put('C', 100); RtoA.put('D', 500); RtoA.put('M', 1000);

    int value = 0;
    for (int i = 0; i < R.length(); i++)
      if (i+1 < R.length() && RtoA.get(R.charAt(i)) < RtoA.get(R.charAt(i+1))) { // check next char first
        value += RtoA.get(R.charAt(i+1)) - RtoA.get(R.charAt(i)); // by definition
        i++; }                                            // skip this char
      else value += RtoA.get(R.charAt(i));
    pr.printf("%d\n", value);
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    while (true) {
      String str = br.readLine();
      if (str == null) break;
      if (Character.isDigit(str.charAt(0))) AtoR(Integer.parseInt(str)); // Arabic to Roman Numerals
      else                                  RtoA(str); // Roman to Arabic Numerals
    }

    pr.close();
  }
}
