import java.math.*;                              // Java code for task 12
class Main {
  public static void main(String[] args) throws Exception {
    BigInteger x = new BigInteger("48112959837082048697"); // Big Integer
    System.out.println(x.isProbablePrime(10) ? "Prime" : "Composite");
  }
}
