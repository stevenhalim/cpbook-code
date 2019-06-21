class Main {                                     // Java code for task 10
  public static void main(String[] args) {
    String S = "line: a70 and z72 will be replaced, aa24 and a872 won't";
    System.out.println(S.replaceAll("\\b+[a-z][0-9][0-9]\\b+", "***"));
  }
}
