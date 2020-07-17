import java.io.*;
import java.util.*;
import java.math.BigInteger;                     // in package java.math

class Main {                                     // UVa 10925 - Krakovia
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(      // use BufferedReader
      new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(            // and PrintWriter
      new BufferedWriter(new OutputStreamWriter(System.out))); // = fast IO
    int caseNo = 0;
    while (true) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      int N = Integer.parseInt(st.nextToken());  // N bills
      int F = Integer.parseInt(st.nextToken());  // F friends
      if (N == 0 && F == 0) break;
      BigInteger sum = BigInteger.ZERO;          // built-in constant
      for (int i = 0; i < N; ++i) {              // sum the N large bills
        BigInteger V = new BigInteger(br.readLine()); // string constructor
        sum = sum.add(V);                        // BigInteger addition
      }
      pw.printf("Bill #%d costs ", ++caseNo);
      pw.printf(sum.toString());
      pw.printf(": each friend should pay ");
      pw.printf(sum.divide(BigInteger.valueOf(F)).toString());
      pw.printf("\n\n");                         // divide to F friends
    }
    pw.close();
  }
}
