public class Three {
  public static void main(String[] args) {
    double max = Double.NEGATIVE_INFINITY;
    double sum = 0.0;
    for (String arg : args) {
      try {
        double num = Double.parseDouble(arg);
        if (num > max) {
          max = num;
        }
        sum += num;
      } catch (NumberFormatException e) {
      }
    }
    System.out.println(max + " " + sum);
  }
}
