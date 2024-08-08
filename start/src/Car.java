
public class Car {
  public void Slogan() {
    System.out.println("Slow is fast");
  }

  int speedDefault = 50;

  public void maxSpeed(int maxSpeed) {
    System.out.println("Max speed: " + maxSpeed);
  }

  public static void main(String[] args) {
    Car myCar = new Car();
    // maxSpeed(myCar.speedDefault);
    myCar.maxSpeed(myCar.speedDefault);
    myCar.Slogan();
  }
}