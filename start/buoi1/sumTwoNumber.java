import java.util.Scanner;

public class sumTwoNumber {
  static void sum() {
    try (Scanner myScan = new Scanner(System.in)) {
      int a = myScan.nextInt();
      int b = myScan.nextInt();
      System.out.println("Sum: " + (a + b));
    }
  }

  public static void main(String[] args) {
    sum();
  }

}