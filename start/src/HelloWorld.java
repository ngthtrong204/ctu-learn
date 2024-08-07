import java.util.Scanner;

public class HelloWorld {
    static int sum(int a, int b) {
        return a + b;
    }

    static float sum(float a, float b) {
        {

            return a + b;
        }
    }

    public static void main(String[] arg) {
        Scanner myScan = new Scanner(System.in);
        int a = myScan.nextInt();
        int b = myScan.nextInt();
        System.out.println(sum(a, b));
        float c = myScan.nextFloat();
        float d = myScan.nextFloat();
        System.out.println(sum(c, d));
    }
}
