import java.util.*;

public class Celsius
{
  public static void main (String [] arg)
  {
    System.out.print("Celcius : ");
    Scanner sc = new Scanner(System.in);
    float celcius = sc.nextFloat();
    celcius=(celcius*9/5)+32;
    System.out.print("Cela fait : " + celcius);
  }
}
