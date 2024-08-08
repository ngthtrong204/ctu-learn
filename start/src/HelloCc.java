
public class HelloCc {
    static int sum(int a, int b) {
        return a + b;
    }

    static float sum(float a, float b) {
        {
            return a + b;
        }
    }

    public static void main(String[] arg) {
        Car myCar = new Car();
        // maxSpeed(myCar.speedDefault);
        myCar.maxSpeed(myCar.speedDefault);
        myCar.maxSpeed(100);
        myCar.Slogan();
    }
}
