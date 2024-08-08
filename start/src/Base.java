abstract class Base {
  public int baseValue = 100;
  public abstract void whatIsThis();
}

class Double extends Base {
  
  public void whatIsThis(int base) {
    System.out.println("This print double value: " + baseValue * 2);
  }
}
