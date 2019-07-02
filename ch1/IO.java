import java.util.*;
import java.io.*;

class IO {
  public static void main(String[] args) throws Exception {
    // comment all lines and only uncomment demo code that you are interested with

    Scanner sc = new Scanner(new File("IO_in1.txt"));
    int TC = sc.nextInt(); // number of test cases
    while (TC-- > 0) { // shortcut to repeat until 0
      int a = sc.nextInt(), b = sc.nextInt(); // compute answer
      System.out.println(a+b); // on the fly
    }

    // Scanner sc = new Scanner(new File("IO_in2.txt"));
    // int a, b;
    // // stop when both integers are 0
    // while (true) {
    //   a = sc.nextInt(); b = sc.nextInt();
    //   if ((a == 0) && (b == 0)) break;
    //   System.out.println(a+b);
    // }

    // Scanner sc = new Scanner(new File("IO_in3.txt"));
    // // Scanner class has hasNext method
    // while (sc.hasNext()) {
    //   int a = sc.nextInt(), b = sc.nextInt();
    //   System.out.println(a+b);
    // }

    // Scanner sc = new Scanner(new File("IO_in3.txt")); // same input file as before
    // int c = 0;
    // while (sc.hasNext()) {
    //   int a = sc.nextInt(), b = sc.nextInt();
    //   // notice the two '\n', Java System.out has printf too
    //   System.out.printf("Case %d: %d\n\n", ++c, a+b);
    // }

    // Scanner sc = new Scanner(new File("IO_in3.txt")); // same input file as before
    // int c = 0;
    // while (sc.hasNext()) {
    //   int a = sc.nextInt(), b = sc.nextInt();
    //   if (c > 0) System.out.println(); // 2nd/more cases
    //   System.out.printf("Case %d: %d\n", ++c, a+b);
    // }

    // Scanner sc = new Scanner(new File("IO_in4.txt"));
    // while (sc.hasNext()) {
    //   int k = sc.nextInt();
    //   int ans = 0, v;
    //   while (k-- > 0) { v = sc.nextInt(); ans += v; }
    //   System.out.println(ans);
    // }

    // Scanner sc = new Scanner(new File("IO_in5.txt"));
    // while (sc.hasNext()) { // keep looping
    //   String[] token = sc.nextLine().split(" ");
    //   int ans = 0;
    //   for (int i = 0; i < token.length; ++i)
    //     ans += Integer.parseInt(token[i]);
    //   System.out.println(ans);
    // }
  }
}
