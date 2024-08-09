import java.util.Scanner;
public class sumTwoNumber {
  static void sum(int a, int b) {
    System.out.println("Sum: " + (a + b));
  }
  public static void main(String[] args) {
    Scanner myScan = new Scanner(System.in);
    int a = myScan.nextInt();
    int b = myScan.nextInt();
    sum(a, b);
  }

}